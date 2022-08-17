#include "PhysicsObject.hpp"

PhysicsObject::PhysicsObject(float x, float y) :
        position(x, y) {}

PhysicsObject::PhysicsObject(float x, float y, float velX, float velY) :
        position(x, y), velocity(velX, velY) {}

PhysicsObject::PhysicsObject(float x, float y, float velX, float velY, float dragX, float dragY) :
        position(x, y), velocity(velX, velY), drag(dragX, dragY) {}

PhysicsObject::PhysicsObject(sf::Vector2f pos) : position(pos) {}

PhysicsObject::PhysicsObject(sf::Vector2f pos, sf::Vector2f vel) :
        position(pos), velocity(vel) {}

PhysicsObject::PhysicsObject(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f drag) :
        position(pos), velocity(vel), drag(drag) {}

const sf::Vector2f &PhysicsObject::getPosition() const {
    return this->position;
}

void PhysicsObject::setPosition(const sf::Vector2f &_position) {
    this->position = _position;
}

const sf::Vector2f &PhysicsObject::getVelocity() const {
    return this->velocity;
}

void PhysicsObject::setVelocity(const sf::Vector2f &_velocity) {
    this->velocity = _velocity;
}

const sf::Vector2f &PhysicsObject::getDrag() const {
    return this->drag;
}

void PhysicsObject::setDrag(const sf::Vector2f &_drag) {
    this->drag = _drag;
}

float PhysicsObject::getFriction() const {
    return this->friction;
}

void PhysicsObject::setFriction(float _friction) {
    this->friction = _friction;
}

void PhysicsObject::physicsUpdate() {

}
