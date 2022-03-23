#pragma once


#include "Item.hpp"

class SwordIron : public Item {
public:
    SwordIron();
    void Use() override;
    void Use2() override;
};

