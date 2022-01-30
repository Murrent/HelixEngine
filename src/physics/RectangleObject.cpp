#include "RectangleObject.hpp"

const sf::Vector2f &RectangleObject::getSize() const {
    return size;
}

void RectangleObject::setSize(const sf::Vector2f &_size) {
    RectangleObject::size = _size;
}

RectangleObject::RectangleObject(float x, float y, float width, float height) : PhysicsObject(x, y, width, height) {
    this->setSize(sf::Vector2f(width, height));
}

RectangleObject::RectangleObject(float x, float y, float width, float height, float velX, float velY) :
        PhysicsObject(x, y, width, height, velX, velY) {

}
