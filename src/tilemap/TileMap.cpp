//
// Created by martin on 2021-04-07.
//

#include <iostream>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cmath>
#include "TileMap.hpp"

bool TileMap::setTileset(const std::string &tileset) {
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;
    return true;
}

bool TileMap::addChunk(sf::Vector2u tileSize, const int *tiles, int x, int y) {
    Chunk chunk;
    if (chunk.load(m_tileset, tileSize, tiles)) {
        chunk.setPosition((float) (x) * Chunk::size, (float) (y) * Chunk::size);
        chunks[x][y] = chunk;
        return true;
    } else
        return false;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &x: chunks) {
        for (auto &y: x.second) {
            target.draw(y.second);
        }
    }
}

void TileMap::setTile(int x, int y, unsigned int tile) {
    sf::Vector2i chunkPos(std::floor(float(x) / float(Chunk::size)), std::floor(float(y) / float(Chunk::size)));
    //std::cout << chunkPos.x << " " << chunkPos.y << std::endl;
    auto gotX = chunks.find(chunkPos.x);
    if (gotX != chunks.end()) {
        auto gotY = chunks[chunkPos.x].find(chunkPos.y);
        if (gotY != chunks[chunkPos.x].end()) {
            chunks[chunkPos.x][chunkPos.y].setTile(x - chunkPos.x * (int) Chunk::size,
                                                   y - chunkPos.y * (int) Chunk::size, tile);
        }
    }
}

void TileMap::removeChunk(sf::Vector2i pos) {
    auto gotX = chunks.find(pos.x);
    if (gotX != chunks.end()) {
        auto gotY = chunks[pos.x].find(pos.y);
        if (gotY != chunks[pos.x].end()) {
            chunks[pos.x].erase(pos.y);
            if (chunks[pos.x].empty())
                chunks.erase(pos.x);
        }
    }
}

unsigned int TileMap::getTileType(int x, int y) {
    sf::Vector2i chunkPos(std::floor(float(x) / float(Chunk::size)), std::floor(float(y) / float(Chunk::size)));
    auto gotX = chunks.find(chunkPos.x);
    if (gotX != chunks.end()) {
        auto gotY = chunks[chunkPos.x].find(chunkPos.y);
        if (gotY != chunks[chunkPos.x].end()) {
            return chunks[chunkPos.x][chunkPos.y].getTileType(x - chunkPos.x * (int) Chunk::size,
                                                              y - chunkPos.y * (int) Chunk::size);
        }
    }
    return 0;
}

unsigned int TileMap::getTileType(float x, float y) {
    return this->getTileType(int(std::floor(x)), int(std::floor(y)));
}
