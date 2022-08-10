#pragma once


#include <SFML/Graphics/RectangleShape.hpp>
#include "items/Item.hpp"
#include "../system/Entity.hpp"

class Inventory : public Entity {
private:
    sf::Vector2u dimensions;
    sf::Vector2i selectedPos{-1, -1};
    std::vector<std::vector<Item *>> items;
    bool active, selected{false};
    sf::RectangleShape background;

public:

    const sf::Vector2u &getDimensions() const;

    std::vector<Item *> getItems();

    Item *getItem(unsigned int x, unsigned int y);

    std::vector<Item *> getHotbarItems();

    void setSize(unsigned int x, unsigned int y);

    void close();

    bool addItem(Item *item);

    bool addItemToSlot(sf::Vector2u pos, Item *item);

    Item *removeItem(sf::Vector2u pos);

    Item *removeItem(Item *item);

    void dropItem(sf::Vector2u invPos, sf::Vector2f worldPos);

    void clear();

    void start() override;

    void update() override;

    void draw() override;
};

