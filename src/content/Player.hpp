#pragma once


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../system/Entity.hpp"
#include "../physics/RectangleObject.hpp"
#include "Inventory.hpp"
#include "Hotbar.hpp"

class Player : public Entity, public RectangleObject {
public:
    sf::RectangleShape shape;
    Inventory inventory;
    bool inventoryOpen{false};
    Hotbar hotbar;
    Item* equippedItem{nullptr};
    bool leftInput{false}, rightInput{false}, jumpInput{false};

    Player() = default;

    Player(float x, float y, float width, float height);

    void setPosition(const sf::Vector2f &_position) override;

    void updateInputs();

    void physicsUpdate() override;

    void draw() override;
};

