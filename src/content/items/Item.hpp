#pragma once


#include <SFML/Graphics/Sprite.hpp>
#include <string>

class Item {
private:
    sf::Sprite sprite;
    std::string name;
    std::string description;
    const unsigned char stackSize{16};
    unsigned char amount{0};

public:
    Item();

    sf::Sprite getSprite();

    std::string getName();

    std::string getDescription();

    unsigned char getStackSize() const;

    unsigned char getAmount() const;

    virtual void Use() = 0;

    virtual void Use2() = 0;

    virtual ~Item();
};

