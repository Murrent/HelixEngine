#pragma once


#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "../../system/Entity.hpp"

class Item : public Entity {
public:
    sf::Sprite sprite;
    std::string name;
    std::string description;
    const unsigned char stackSize{16};
    unsigned char amount{1};

    Item();

    Item(unsigned char _stackSize);

    virtual void Use() = 0;

    virtual void Use2() = 0;

    void start() override;

    void update() override;

    void draw() override;

    virtual ~Item();
};

