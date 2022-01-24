#include <cstdio>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

float DotProduct(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.x + a.y * b.y;
}

float Distance(sf::Vector2f a, sf::Vector2f b) {
    float distX = a.x - b.x;
    float distY = a.y - b.y;
    return std::sqrt(distX * distX + distY * distY);
}

struct AABB {
    sf::Vector2f min;
    sf::Vector2f max;
};

bool AABBvsAABB(AABB a, AABB b) {
    // Exit with no intersection if found separated along an axis
    if (a.max.x < b.min.x or a.min.x > b.max.x) return false;
    if (a.max.y < b.min.y or a.min.y > b.max.y) return false;

    // No separating axis found, therefor there is at least one overlapping axis
    return true;
}

class Body {
public:
    sf::Vector2f velocity, pos;
    float restitution{}, mass{}, invMass{};

    void SetMass(float _mass) {
        this->mass = _mass;
        invMass = 1 / _mass;
    }

    Body(float x, float y, float mass) {
        pos.x = x;
        pos.y = y;
        SetMass(mass);
    }

    Body() {
        SetMass(1.f);
    }
};


void ResolveCollision(Body &A, Body &B) {
    // Calculate relative velocity
    sf::Vector2f rv = B.velocity - A.velocity;
    float dist = Distance(B.pos, A.pos);
    if (dist == 0.f) return;
    sf::Vector2f normal = (B.pos - A.pos) / dist;

    // Calculate relative velocity in terms of the normal direction
    float velAlongNormal = DotProduct(rv, normal);

    // Do not resolve if velocities are separating
    if (velAlongNormal > 0)
        return;

    // Calculate restitution
    float e = std::min(A.restitution, B.restitution);

    // Calculate impulse scalar
    float j = -(1 + e) * velAlongNormal;
    j /= A.invMass + B.invMass;

    // Apply impulse
    sf::Vector2f impulse = j * normal;
    A.velocity -= A.invMass * impulse;
    B.velocity += B.invMass * impulse;
}

struct Circle : public Body {
    sf::CircleShape shape;
    float radius{};

    Circle() {
        radius = 15;
    }

    void SetRadius(float rad) {
        this->radius = rad;
        this->shape.setRadius(rad);
        this->shape.setOrigin(rad, rad);
    }

    void SetPosition(float x, float y) {
        this->pos.x = x;
        this->pos.y = y;
        this->shape.setPosition(x, y);
    }
};

void CirclePosResolution(Circle &a, Circle &b) {
    sf::Vector2f normal = b.pos - a.pos;
    sf::Vector2f midPoint = normal / 2.f;

    float dist = Distance(b.pos, a.pos);
    if (dist == 0.f) return;
    sf::Vector2f normalized = normal / dist;

    a.pos = a.pos + midPoint - normalized * a.radius;
    b.pos = a.pos + midPoint + normalized * a.radius;
}

bool CirclevsCircleUnoptimized(const Circle &a, const Circle &b) {
    float r = a.radius + b.radius;
    float distX = a.pos.x - b.pos.x;
    float distY = a.pos.y - b.pos.y;
    return r * r > distX * distX + distY * distY;
}

bool CirclevsCircleOptimized(const Circle &a, const Circle &b) {
    float r = a.radius + b.radius;
    r *= r;
    return r > (a.pos.x + b.pos.x) * (a.pos.x + b.pos.x) + (a.pos.y + b.pos.y) * (a.pos.y + b.pos.y);
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(60);

    Circle circles[100];
    for (auto &circle : circles) {
        circle.SetMass(1);
        circle.SetRadius(15);
    }
    circles[0].velocity = sf::Vector2f(0.2f, 0.01f);
    circles[0].shape.setFillColor(sf::Color::Green);

    for (int i = 0; i < 100; ++i) {
        circles[i].SetPosition(50.f + float(i % 10) * 50.f, 50.f + std::floor(float(i) / 10.f) * 50.f);
        circles[i].restitution = 0.f;
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        for (auto &circle : circles) {
            if (circle.pos.x < 0.f) {
                circle.velocity.x = -circle.velocity.x;
                circle.SetPosition(0.f, circle.pos.y);
            } else if (circle.pos.x > (float) window.getSize().x) {
                circle.velocity.x = -circle.velocity.x;
                circle.SetPosition((float) window.getSize().x, circle.pos.y);
            }
            if (circle.pos.y < 0.f) {
                circle.velocity.y = -circle.velocity.y;
                circle.SetPosition(circle.pos.x, 0.f);
            } else if (circle.pos.y > (float) window.getSize().y) {
                circle.velocity.y = -circle.velocity.y;
                circle.SetPosition(circle.pos.x, (float) window.getSize().y);
            }
            circle.SetPosition(circle.pos.x + circle.velocity.x, circle.pos.y + circle.velocity.y + 1.0f);
        }
        for (int i = 0; i < 100; ++i) {
            for (int j = i + 1; j < 100; ++j) {
                if (CirclevsCircleUnoptimized(circles[i], circles[j])) {
                    ResolveCollision(circles[i], circles[j]);
                    CirclePosResolution(circles[i], circles[j]);
                }
            }
        }

        window.clear(sf::Color(150, 150, 150));

        for (auto &circle : circles) {
            window.draw(circle.shape);
            sf::Vertex point(circle.pos, sf::Color::Black);
            window.draw(&point, 1, sf::Points);
        }
        window.display();
    }
    return EXIT_SUCCESS;
}