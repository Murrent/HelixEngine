#pragma once


#include "../content/items/Item.hpp"
#include "Entity.hpp"

class ItemManager : public Entity {
private:
    std::vector<Item*> items;

public:

    void draw() override;
};

