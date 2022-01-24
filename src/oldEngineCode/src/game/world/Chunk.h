//
// Created by Martin on 2021-01-01.
//

#ifndef GAMEENGINE_CHUNK_H
#define GAMEENGINE_CHUNK_H


#include "Tile.h"
#include <SFML/Graphics/RenderTarget.hpp>

class Chunk {
public:
    static constexpr int size = 16;
private:
    sf::Vector2i offset;
    Tile tiles[size][size];
public:
    explicit Chunk(sf::Vector2i _offset);
    void Fill(sf::Texture& texture);
    void SetTile(Tile* tile, sf::Texture& texture);
    void SetTile(sf::Vector2i pos, sf::Texture& texture);
    void SetTile(int x, int y, sf::Texture& texture);
    void RemoveTile(Tile* tile);
    void RemoveTile(sf::Vector2i pos);
    void RemoveTile(int x, int y);
    Tile* GetTile(sf::Vector2i pos);
    Tile* GetTile(int x, int y);
    bool ShouldDraw(Tile* tile);
    bool ShouldDraw(sf::Vector2i pos);
    bool ShouldDraw(int x, int y);
    void Draw(sf::RenderTarget& renderTarget);
};


#endif //GAMEENGINE_CHUNK_H
