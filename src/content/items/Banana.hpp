#pragma once


#include "Item.hpp"

class Banana : public Item {
public:
    Banana();
    void Use() override;
    void Use2() override;
};

