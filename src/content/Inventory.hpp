#pragma once


#include "items/Item.hpp"

class Inventory {
private:
    std::unordered_map<int, std::unordered_map<int, Item *>> items;
    
public:
    bool addItem(Item &item);

    bool addItemToSlot(sf::Vector2u pos, Item &item);

    bool dropItem(sf::Vector2u pos);
};

