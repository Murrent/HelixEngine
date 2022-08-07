#pragma once


#include "TileMap.hpp"

class MapGenerator {
public:
    static bool initialGeneration(TileMap &tileMap, const std::string &tileset);
};

