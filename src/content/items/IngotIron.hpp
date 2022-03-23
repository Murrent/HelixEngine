#pragma once


#include "Item.hpp"

class IngotIron : public Item {
public:
    IngotIron();
    void Use() override;
    void Use2() override;
};

