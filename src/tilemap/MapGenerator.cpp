#include "MapGenerator.hpp"
#include "../noise/SimplexNoise.hpp"
#include "../common/Random.hpp"

bool MapGenerator::initialGeneration(TileMap &tileMap, const std::string &tileset) {
    rngRefreshSeed();

    if (!tileMap.setTileset(tileset))
        return false;

    int noiseLevel[256];
    sf::Vector2i offset(0,0);
    sf::Vector2f scale(0.5f,0.5f);
    sf::Vector2f seedOffset(0,0);
    for (int x = -5; x < 5; ++x) {
        offset.x = x;
        for (int y = -4; y < 3; ++y) {
            offset.y = y;
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 16; j++) {
                    noiseLevel[i + j * 16] = int((SimplexNoise::noise((float)(i * offset.x + seedOffset.x) * scale.x, (float)(j * offset.y + seedOffset.y) * scale.y) + 1.0f) * 0.5f * 4.0f);
                }
            }

            if (!tileMap.addChunk(sf::Vector2u(4, 4), noiseLevel, offset.x, offset.y))
                return false;
        }
    }


    return true;
}
