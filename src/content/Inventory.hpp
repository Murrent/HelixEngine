#pragma once


#include "items/Item.hpp"

class Inventory {
private:
    sf::Vector2u dimensions;
    std::vector<std::vector<Item *>> items;

public:
    std::vector<Item *> getItems();

    void setSize(unsigned int x, unsigned int y);

    bool addItem(Item *item);

    bool addItemToSlot(sf::Vector2u pos, Item *item);

    bool dropItem(sf::Vector2u pos);
};

