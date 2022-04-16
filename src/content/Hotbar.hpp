#pragma once

#include <vector>
#include "../system/Entity.hpp"
#include "items/Item.hpp"

class Hotbar : public Entity {
public:
    unsigned int size, selected;
    std::vector<Item *> items;

    Hotbar();

    Hotbar(unsigned int slots, unsigned int selectedSlot);

    void update() override;

    void draw() override;
};

