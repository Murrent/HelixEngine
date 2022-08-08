#include "Item.hpp"
#include "../../scene/GameManager.hpp"

Item::Item() = default;

Item::Item(unsigned char _stackSize) : stackSize(_stackSize) {}

Item::~Item() = default;

void Item::update() {
    Entity::update();
}

void Item::start() {
    Entity::start();
}

void Item::draw() {
    GameManager::window.draw(this->sprite);
}

void Item::Use() {

}

void Item::Use2() {

}
