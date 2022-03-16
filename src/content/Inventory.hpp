#pragma once


#include <SFML/Graphics/RectangleShape.hpp>
#include "items/Item.hpp"
#include "../system/Entity.hpp"

class Inventory : public Entity {
private:
    sf::Vector2u dimensions;
    std::vector<std::vector<Item *>> items;
    bool active;
    sf::RectangleShape background;

public:
    std::vector<Item *> getItems();

    void setSize(unsigned int x, unsigned int y);

    bool addItem(Item *item);

    bool addItemToSlot(sf::Vector2u pos, Item *item);

    Item* removeItem(sf::Vector2u pos);

    void start() override;

    void update() override;

    void draw() override;
};

