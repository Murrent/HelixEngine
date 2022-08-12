#pragma once


#include "TileMap.hpp"

class MapGenerator {
public:
    static bool initialGeneration(TileMap &tileMap, const std::string &tileset, unsigned int seed);
    static bool generateChunk(TileMap &tileMap, int x, int y);
};

