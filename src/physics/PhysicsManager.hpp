#pragma once

#include <vector>
#include "RectangleObject.hpp"
#include "CircleObject.hpp"
#include "../system/Entity.hpp"

class PhysicsManager {
private:
    static bool checkLeftVel(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation, TileMap &map,
                             sf::Vector2i &tile);

    static bool checkRightVel(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation, TileMap &map,
                              sf::Vector2i &tile);

    static bool checkUpVel(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation, TileMap &map,
                           sf::Vector2i &tile);

    static bool checkDownVel(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation, TileMap &map,
                             sf::Vector2i &tile);

    static bool continousRectCheckX(RectangleObject &obj, sf::Vector2f dest, sf::Vector2u tileOccupation, TileMap &map);

    static bool continousRectCheckY(RectangleObject &obj, sf::Vector2f dest, sf::Vector2u tileOccupation, TileMap &map);

public:
    std::vector<RectangleObject *> rectangles;
    std::vector<CircleObject *> circles;

    //Dynamic rectangle to static rectangle response solver
    static void rectTilemap(RectangleObject &obj, TileMap &map);


    //Dynamic circle to static rectangle response solver
    void circleTilemap(CircleObject &obj, TileMap &map);

    void update(TileMap &map);
};

