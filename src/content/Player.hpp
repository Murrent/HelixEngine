#pragma once


#include <SFML/Graphics/RectangleShape.hpp>
#include "../system/Entity.hpp"
#include "../physics/RectangleObject.hpp"

class Player : public Entity, public RectangleObject {
public:
    sf::RectangleShape shape;

    Player() = default;

    Player(float x, float y, float width, float height);

    void setPosition(const sf::Vector2f &_position) override;
};

