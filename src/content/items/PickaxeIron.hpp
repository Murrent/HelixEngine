#pragma once


#include "Item.hpp"

class PickaxeIron : public Item {
public:
    PickaxeIron();
    void Use() override;
    void Use2() override;
};

