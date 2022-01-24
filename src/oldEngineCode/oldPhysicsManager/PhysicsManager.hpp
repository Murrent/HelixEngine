#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>

using namespace sf;

class RoundLine {
public:
    Vector2f start, end;
    static constexpr float radius = 20.f;
    VertexArray array;
    CircleShape startShape, endShape;

    void UpdateArray();
};

class Circle {
public:
    Vector2f pos, vel;
    float mass{1.f}, elasticity{1.0f};
    static constexpr float radius = 20.f;
    CircleShape shape;
};

class PhysicsManager {
private:
    void CirclePointResponse(Circle& circle, Vector2f point);
    bool CircleLineCheck(Circle& circle, RoundLine& line, Vector2f& point);
public:
    std::vector<RoundLine> staticLines;
    std::vector<Circle> circles;

    void Init();

    void Update();

    void Draw(RenderWindow &window);
};

