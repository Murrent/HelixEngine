#pragma once


#include "PhysicsObject.hpp"

class CircleObject : public PhysicsObject {
protected:
    float radius{0.5f};
public:
    [[nodiscard]] float getRadius() const;

    void setRadius(float _radius);
};

