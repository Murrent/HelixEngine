#pragma once


#include "TileMap.hpp"

class MapGenerator {
public:
    static bool setup(TileMap &tileMap, const std::string &tileset, unsigned int seed, const std::string &worldName);
    static bool generateChunk(TileMap &tileMap, int x, int y);
};

