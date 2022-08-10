#include "ItemObject.hpp"
#include "../scene/GameManager.hpp"

ItemObject::ItemObject(Item *_item)
        : item(_item), RectangleObject(0, 0, 0.5f, 0.5f) {
    this->sprite = this->item->sprite;
    this->sprite.setColor(sf::Color::White);
    sf::Rect<int> rect = this->sprite.getTextureRect();
    this->setSize(sf::Vector2f((float)rect.width, (float)rect.height) * 0.125f * 0.99f);
    this->sprite.setOrigin((float)rect.width * 0.5f, (float)rect.height * 0.5f);
    clock.restart();
}

ItemObject::ItemObject(Item *_item, float x, float y)
        : item(_item), RectangleObject(x, y, 0.5f, 0.5f, 0, 0) {
    this->sprite = this->item->sprite;
    this->sprite.setColor(sf::Color::White);
    sf::Rect<int> rect = this->sprite.getTextureRect();
    this->setSize(sf::Vector2f((float)rect.width, (float)rect.height) * 0.125f * 0.99f);
    this->sprite.setOrigin((float)rect.width * 0.5f, (float)rect.height * 0.5f);
    clock.restart();
}

ItemObject::ItemObject(Item *_item, float x, float y, float velX, float velY)
        : item(_item), RectangleObject(x, y, 0.5f, 0.5f, velX, velY) {
    this->sprite = this->item->sprite;
    this->sprite.setColor(sf::Color::White);
    sf::Rect<int> rect = this->sprite.getTextureRect();
    this->setSize(sf::Vector2f((float)rect.width, (float)rect.height) * 0.125f * 0.99f);
    this->sprite.setOrigin((float)rect.width * 0.5f, (float)rect.height * 0.5f);
    clock.restart();
}

void ItemObject::start() {
    Entity::start();
}

void ItemObject::update() {
    Entity::update();
    sf::Vector2f vel = getVelocity();
    vel.x *= 0.9f;
    vel.y *= 0.9f;
    setVelocity(vel);
}

void ItemObject::draw() {
    Entity::draw();
    this->sprite.setPosition(this->getPosition());
    this->sprite.setScale(0.25f, 0.25f);
    sf::RectangleShape shape;
    shape.setPosition(this->getPosition());
    sf::Rect<int> rect = this->sprite.getTextureRect();
    shape.setSize(sf::Vector2f(rect.width, rect.height) * 0.25f);
    shape.setOrigin(rect.width * 0.125f, rect.height * 0.125f);
    //GameManager::window.draw(shape);
    GameManager::window.draw(this->sprite);
}
