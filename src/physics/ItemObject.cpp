#include "ItemObject.hpp"

ItemObject::ItemObject(Item *_item)
        : item(_item) {

}

ItemObject::ItemObject(Item *_item, float x, float y)
        : item(_item), RectangleObject(x, y, 0.5f, 0.5f) {

}

ItemObject::ItemObject(Item *_item, float x, float y, float velX, float velY)
        : item(_item), RectangleObject(x, y, 0.5f, 0.5f, velX, velY) {

}

void ItemObject::start() {
    //this->sprite = this->item->getSprite();
    //this->name = this->item->getName();
    //this->amount = this->item->getAmount();
}

void ItemObject::update() {
    Entity::update();
}

void ItemObject::draw() {
    Entity::draw();
}
