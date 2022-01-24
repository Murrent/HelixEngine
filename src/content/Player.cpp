#include "Player.hpp"


Player::Player(float x, float y, float width, float height) : RectangleObject(x, y, width, height) {
    this->shape.setSize(2.0f * sf::Vector2f(width, height));
    this->shape.setPosition(x, y);
    this->shape.setOrigin(width, height);
}

void Player::setPosition(const sf::Vector2f &_position) {
    PhysicsObject::setPosition(_position);
    this->shape.setPosition(_position);
}
