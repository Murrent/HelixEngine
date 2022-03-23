#pragma once


#include "Item.hpp"

class Stick : public Item {
public:
    Stick();
    void Use() override;
    void Use2() override;
};

