#pragma once


#include "PhysicsObject.hpp"

class RectangleObject : public PhysicsObject {
protected:
    sf::Vector2f size;
public:
    RectangleObject() = default;

    RectangleObject(float x, float y, float width, float height);

    RectangleObject(float x, float y, float width, float height, float velX, float velY);

    [[nodiscard]] const sf::Vector2f &getSize() const;

    void setSize(const sf::Vector2f &size);
};

