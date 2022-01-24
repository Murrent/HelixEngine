#pragma once


#include <SFML/Graphics/Sprite.hpp>
#include <string>

class Item {
private:
    sf::Sprite sprite;
    std::string name;
    std::string description;
    const unsigned char stackSize{16};

public:
    virtual void Use() = 0;

    virtual void Use2() = 0;
};

