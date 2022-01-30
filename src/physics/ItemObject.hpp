#pragma once


#include "RectangleObject.hpp"
#include "../system/Entity.hpp"
#include "../content/items/Item.hpp"

class ItemObject : public Entity, public RectangleObject {
public:
    sf::Sprite sprite;
    std::string name;
    unsigned char amount{0};
    Item *item{};

    explicit ItemObject(Item *_item);

    ItemObject(Item *_item, float x, float y);

    ItemObject(Item *_item, float x, float y, float velX, float velY);

    void start() override;

    void update() override;

    void draw() override;
};
