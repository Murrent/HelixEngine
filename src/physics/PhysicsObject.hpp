#pragma once


#include "../tilemap/TileMap.hpp"

class PhysicsObject {
protected:
    sf::Vector2f position, velocity, drag;
    float friction{0.5f};
public:

    PhysicsObject() = default;

    PhysicsObject(float x, float y);

    PhysicsObject(float x, float y, float velX, float velY);

    PhysicsObject(float x, float y, float velX, float velY, float dragX, float dragY);

    explicit PhysicsObject(sf::Vector2f pos);

    PhysicsObject(sf::Vector2f pos, sf::Vector2f vel);

    PhysicsObject(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f drag);

    [[nodiscard]] virtual const sf::Vector2f &getPosition() const;

    virtual void setPosition(const sf::Vector2f &_position);

    [[nodiscard]] virtual const sf::Vector2f &getVelocity() const;

    virtual void setVelocity(const sf::Vector2f &_velocity);

    [[nodiscard]] virtual const sf::Vector2f &getDrag() const;

    virtual void setDrag(const sf::Vector2f &_drag);

    [[nodiscard]] virtual float getFriction() const;

    virtual void setFriction(float _friction);

    virtual void physicsUpdate();
};

