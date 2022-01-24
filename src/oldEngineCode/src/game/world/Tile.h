//
// Created by Martin on 2021-01-17.
//

#ifndef GAMEENGINE_TILE_H
#define GAMEENGINE_TILE_H


#include <SFML/Graphics/Sprite.hpp>

class Tile {
public:
    sf::Sprite sprite;
    bool draw;
    Tile();
};


#endif //GAMEENGINE_TILE_H
