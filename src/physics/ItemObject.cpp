#include "ItemObject.hpp"
#include "../scene/GameManager.hpp"

ItemObject::ItemObject(Item *_item)
        : item(_item), RectangleObject(0, 0, 0.5f, 0.5f) {
    this->sprite = this->item->sprite;
    this->name = this->item->name;
    this->amount = this->item->amount;
    this->sprite.setColor(sf::Color::White);
    sf::Rect<int> rect = this->sprite.getTextureRect();
    this->setSize(sf::Vector2f(rect.width, rect.height) * 0.125f);
}

ItemObject::ItemObject(Item *_item, float x, float y)
        : item(_item), RectangleObject(x, y, 0.5f, 0.5f, 0, 0) {
    this->sprite = this->item->sprite;
    this->name = this->item->name;
    this->amount = this->item->amount;
    this->sprite.setColor(sf::Color::White);
    sf::Rect<int> rect = this->sprite.getTextureRect();
    this->setSize(sf::Vector2f(rect.width, rect.height) * 0.125f);
}

ItemObject::ItemObject(Item *_item, float x, float y, float velX, float velY)
        : item(_item), RectangleObject(x, y, 0.5f, 0.5f, velX, velY) {
    this->sprite = this->item->sprite;
    this->name = this->item->name;
    this->amount = this->item->amount;
    this->sprite.setColor(sf::Color::White);
    sf::Rect<int> rect = this->sprite.getTextureRect();
    this->setSize(sf::Vector2f(rect.width, rect.height) * 0.125f);
}

void ItemObject::start() {
    Entity::start();
}

void ItemObject::update() {
    Entity::update();
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
