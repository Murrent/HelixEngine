//
// Created by Martin on 2021-01-02.
//

#ifndef GAMEENGINE_SHAPE_H
#define GAMEENGINE_SHAPE_H
#include <SFML/System/Vector2.hpp>

class Shape {
public:
    sf::Vector2f position, velocity, gravity, force;
    float rotation{}, angularVelocity{}, torque{}, inertia{}, mass{}, friction{};
    Shape();
    virtual void Update(float delta);
    void AddForce(sf::Vector2f _force);
    void AddTorque(float _torque);
    void AddForceAtPosition(sf::Vector2f _pos, sf::Vector2f _force);
    void AddImpulseAtPosition(sf::Vector2f _pos, sf::Vector2f _impulse);
};


#endif //GAMEENGINE_SHAPE_H
