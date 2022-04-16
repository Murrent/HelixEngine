#pragma once


#include <SFML/Graphics/RectangleShape.hpp>
#include "items/Item.hpp"
#include "../system/Entity.hpp"

class Inventory : public Entity {
private:
    sf::Vector2u dimensions, selectedPos;
    std::vector<std::vector<Item *>> items;
    bool active, selected;
    sf::RectangleShape background;

public:

    std::vector<Item *> getItems();

    Item *getItem(unsigned int x, unsigned int y);

    std::vector<Item *> getHotbarItems();

    void setSize(unsigned int x, unsigned int y);

    bool addItem(Item *item);

    bool addItemToSlot(sf::Vector2u pos, Item *item);

    Item *removeItem(sf::Vector2u pos);

    void start() override;

    void update() override;

    void draw() override;
};

