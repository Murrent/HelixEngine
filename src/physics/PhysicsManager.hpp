#pragma once

#include <vector>
#include "RectangleObject.hpp"
#include "CircleObject.hpp"
#include "../system/Entity.hpp"
#include "../content/items/Item.hpp"
#include "ItemObject.hpp"
#include "../content/Player.hpp"

class PhysicsManager : public Entity {
private:
    static constexpr float updateDelay = 1.0f / 60.0f;
    float timeHandled = 0.0f;
    sf::Clock tickClock;

    static bool checkArea(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation, sf::Vector2i &tile);

    static bool
    checkLeftVel(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation, sf::Vector2i &tile);

    static bool
    checkRightVel(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation, sf::Vector2i &tile);

    static bool
    checkUpVel(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation, sf::Vector2i &tile);

    static bool
    checkDownVel(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation, sf::Vector2i &tile);

    static bool continousRectCheckX(RectangleObject &obj, sf::Vector2f dest, sf::Vector2u tileOccupation);

    static bool continousRectCheckY(RectangleObject &obj, sf::Vector2f dest, sf::Vector2u tileOccupation);

    static bool continousRectCheckXPlayer(RectangleObject &obj, sf::Vector2f dest, sf::Vector2u tileOccupation);

    void updatePhysics();

public:
    std::vector<Player *> players;
    std::vector<RectangleObject *> stdRects;
    std::vector<ItemObject> itemRects;
    std::vector<CircleObject *> circles;

    sf::Vector2f gravity{0.0f, 0.1f};

    //Dynamic rectangle to static rectangle response solver
    static void rectTilemap(RectangleObject &obj);

    //Dynamic rectangle to static rectangle response solver with extra functionality
    static void playerTilemap(RectangleObject &obj);

    //Dynamic circle to static rectangle response solver
    void circleTilemap(CircleObject &obj);

    void start() override;

    void update() override;

    void draw() override;

    void addStdRect(RectangleObject *obj);

    void addItem(Item *item, float x, float y);

    void addItem(Item *item, float x, float y, float velX, float velY);
};

