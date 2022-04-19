#pragma once

#include <vector>
#include <iostream>
#include "VerletObject.hpp"
#include "VectorMath.hpp"
#include "Link.hpp"

class Solver {
public:
    sf::Vector2f gravity = {0.0f, 0.0f};

    void update(std::vector<VerletObject> &objects, std::vector<Link>& links, float dt) {
        const uint32_t subSteps = 1;
        const float subStepsMultiplier = 1.0f / (float)subSteps;
        const float delta = dt * subStepsMultiplier;
        for (int i = 0; i < subSteps; ++i) {
            applyGravity(objects);
            for (auto& link : links) {
                link.apply(objects);
            }
            applyConstraint(objects);
            solveCollisions(objects);
            updatePositions(objects, delta);
        }
    }

    void updatePositions(std::vector<VerletObject> &objects, float dt) {
        for (auto &obj : objects) {
            obj.updatePos(dt);
        }
    }

    void applyGravity(std::vector<VerletObject> &objects) {
        for (auto &obj : objects) {
            obj.accelerate(gravity);
        }
    }

    void applyConstraint(std::vector<VerletObject> &objects) {
        const sf::Vector2f position(0, 0);
        const float radius = 300.0f;

        for (auto &obj : objects) {
            if (obj.staticBody) continue;
            const sf::Vector2f normal = Normal(obj.position, position);
            //std::cout << normal.x << " " << normal.y << std::endl;
            const sf::Vector2f to_obj = obj.position - position;
            const float dist = Dist(sf::Vector2f(0, 0), to_obj);
            if (dist > radius - obj.size) {
                const sf::Vector2f n = to_obj / dist;
                obj.position = position + n * (300.0f - obj.size);// normal * (300.0f - obj.size);
                //obj.prevPosition = obj.position;
            }
        }
    }

    void solveCollisions(std::vector<VerletObject> &objects) {
        const uint32_t count = objects.size();
        for (uint32_t i = 0; i < count; ++i) {
            auto& obj1 = objects[i];
            for (uint32_t k = i + 1; k < count; ++k) {
                auto& obj2 = objects[k];
                const sf::Vector2f axis = obj1.position - obj2.position;
                const float dist = Dist(sf::Vector2f(0, 0), axis);
                if (dist < obj1.size + obj2.size) {
                    const sf::Vector2f n = axis / dist;
                    const float delta = (obj1.size + obj2.size) - dist;
                    const float scale = 1 / (obj1.size * obj1.size + obj2.size * obj2.size);
                    // Scale was initially 0.5f but this was changed to make larger objects move less by small objects
                    if (!obj1.staticBody)
                        obj1.position += scale * obj2.size * obj2.size * delta * n;
                    if (!obj2.staticBody)
                        obj2.position -= scale * obj1.size * obj1.size * delta * n;
                }

            }
        }
    }
};

