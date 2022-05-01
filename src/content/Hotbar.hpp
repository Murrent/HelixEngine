#pragma once

#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../system/Entity.hpp"
#include "items/Item.hpp"

class Hotbar : public Entity {
public:
    unsigned int size, selected;
    std::vector<Item *> items;
    sf::RectangleShape background;

    Hotbar();

    Hotbar(unsigned int slots, unsigned int selectedSlot);

    Item* getSelectedItem();

    void dropEquippedItem(sf::Vector2f velocity);

    void start() override;

    void update() override;

    void draw() override;
};

