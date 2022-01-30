#include "Item.hpp"

Item::Item() {}

Item::~Item() {

}

sf::Sprite Item::getSprite() {
    return this->sprite;
}

std::string Item::getName() {
    return this->name;
}

std::string Item::getDescription() {
    return this->description;
}

unsigned char Item::getStackSize() const {
    return this->stackSize;
}

unsigned char Item::getAmount() const {
    return this->amount;
}
