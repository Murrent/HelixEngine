#pragma once


#include <iostream>
#include "Item.hpp"

class Stick : public Item {
public:
    Stick();
    void Use() override;
    void Use2() override;

    ~Stick() {
        std::cout << "stick destroyed" << std::endl;
    }
};

