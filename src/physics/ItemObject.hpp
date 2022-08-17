#pragma once


#include <SFML/System/Clock.hpp>
#include "RectangleObject.hpp"
#include "../system/Entity.hpp"
#include "../content/items/Item.hpp"

class ItemObject : public Entity, public RectangleObject {
public:
    sf::Sprite sprite;
    Item *item{};
    static constexpr float noPickupTime = 2.0f;
    sf::Clock clock;

    explicit ItemObject(Item *_item);

    ItemObject(Item *_item, float x, float y);

    ItemObject(Item *_item, float x, float y, float velX, float velY);

    void start() override;

    void update() override;

    void physicsUpdate() override;

    void draw() override;
};
