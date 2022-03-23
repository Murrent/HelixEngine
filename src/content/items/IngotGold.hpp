#pragma once


#include "Item.hpp"

class IngotGold : public Item {
public:
    IngotGold();
    void Use() override;
    void Use2() override;
};

