//
// Created by Martin on 2021-01-02.
//

#include "Shape.h"
#include "physics.h"
#include <stdio.h>

void Shape::Update(float delta) {
    sf::Vector2f acceleration = force / mass + gravity;
    velocity += acceleration * delta;
    position += velocity * delta;
    float angularAcceleration = torque / inertia;
    angularVelocity += angularAcceleration * delta;
    rotation += angularVelocity * delta;
    force = sf::Vector2f(0.0f,0.0f);
    torque = 0;
    //printf("%f - %f \n", position.x, position.y);
}

void Shape::AddForce(sf::Vector2f _force) {
    force += _force;
}

void Shape::AddTorque(float _torque) {
    torque += _torque;
}

void Shape::AddForceAtPosition(sf::Vector2f _pos, sf::Vector2f _force) {
    AddForce(_force);
    AddTorque(Physics::Cross(_pos, force));
}

void Shape::AddImpulseAtPosition(sf::Vector2f _pos, sf::Vector2f _impulse) {
    velocity += _impulse * -mass;
    angularVelocity += Physics::Cross(_pos, _impulse) * -inertia;
}

Shape::Shape() {
    sf::Vector2f position = velocity = gravity = force = sf::Vector2f(0,0);
    float rotation = angularVelocity = torque = inertia = mass = friction = 0;
}


