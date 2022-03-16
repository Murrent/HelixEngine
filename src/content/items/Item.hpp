#pragma once


#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "../../system/Entity.hpp"

class Item : public Entity {
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

    void start() override;

    void update() override;

    void draw() override;

    virtual ~Item();
};

