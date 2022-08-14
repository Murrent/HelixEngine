#include <iostream>
#include "MapGenerator.hpp"
#include "../noise/SimplexNoise.hpp"
#include "../common/Random.hpp"

bool MapGenerator::setup(TileMap &tileMap, const std::string &tileset, unsigned int seed, const std::string &worldName) {
    if (!tileMap.setTileset(tileset))
        return false;

    tileMap.worldName = worldName;

    tileMap.seed = seed;

    rngSetSeed(tileMap.seed);

    tileMap.scaleHeight = sf::Vector2f(0.03f, 0.03f);
    tileMap.seedOffsetHeight = sf::Vector2f(rngF01() * 1000.0f, rngF01() * 1000.0f);
    tileMap.scaleCave = sf::Vector2f(0.03f, 0.03f);
    tileMap.seedOffsetCave = sf::Vector2f(rngF01() * 1000.0f, rngF01() * 1000.0f);
    tileMap.scaleIron = sf::Vector2f(0.03f, 0.03f);
    tileMap.seedOffsetIron = sf::Vector2f(5000, 5000);
    tileMap.scaleGold = sf::Vector2f(0.03f, 0.03f);
    tileMap.seedOffsetGold = sf::Vector2f(rngF01() * 1000.0f, rngF01() * 1000.0f);
    tileMap.scaleDirt = sf::Vector2f(0.03f, 0.03f);
    tileMap.seedOffsetDirt = sf::Vector2f(rngF01() * 1000.0f, rngF01() * 1000.0f);
    tileMap.terrainAmplitude = 16.0f;

    return true;
}

bool MapGenerator::generateChunk(TileMap &tileMap, int x, int y) {
    //rngSetSeed(tileMap.seed);
    if (y == 0)
        generateChunk(tileMap, x, y - 1);

    int noiseLevel[Chunk::size * Chunk::size * 2];
    sf::Vector2i offset(x, y);

    for (int i = 0; i < Chunk::size; i++) {
        float heightNoise = SimplexNoise::noise(
                ((float) i + (float) (offset.x * (int) Chunk::size) + tileMap.seedOffsetHeight.x) *
                tileMap.scaleHeight.x) *
                            (float) tileMap.terrainAmplitude;

        for (int j = 0; j < Chunk::size; j++) {
            noiseLevel[i + j * Chunk::size] = 0;
            noiseLevel[i + j * Chunk::size + Chunk::size * Chunk::size] = 0;

            float height = (float) j + (float) (offset.y * (int) Chunk::size);
            if (heightNoise > height) {
                noiseLevel[i + j * Chunk::size] = 0;
            } else {
                if (std::ceil(heightNoise) == std::ceil(height)) {
                    noiseLevel[i + j * Chunk::size] = 5;
                    noiseLevel[i + j * Chunk::size + Chunk::size * Chunk::size] = 5;
                } else if (heightNoise > height - 10) {
                    noiseLevel[i + j * Chunk::size] = 4;
                    noiseLevel[i + j * Chunk::size + Chunk::size * Chunk::size] = 4;
                } else {
                    noiseLevel[i + j * Chunk::size + Chunk::size * Chunk::size] = 1;
                }
                float noiseResult =
                        (SimplexNoise::noise(
                                ((float) i + (float) (offset.x * (int) Chunk::size) + tileMap.seedOffsetCave.x) *
                                tileMap.scaleCave.x,
                                ((float) j + (float) (offset.y * (int) Chunk::size) + tileMap.seedOffsetCave.y) *
                                tileMap.scaleCave.y) +
                         1.0f) * 0.5f;
                float noiseResultIron =
                        (SimplexNoise::noise(
                                ((float) i + (float) (offset.x * (int) Chunk::size) + tileMap.seedOffsetIron.x) *
                                tileMap.scaleIron.x,
                                ((float) j + (float) (offset.y * (int) Chunk::size) + tileMap.seedOffsetIron.y) *
                                tileMap.scaleIron.y) +
                         1.0f) * 0.5f;
                float noiseResultGold =
                        (SimplexNoise::noise(
                                ((float) i + (float) (offset.x * (int) Chunk::size) + tileMap.seedOffsetGold.x) *
                                tileMap.scaleGold.x,
                                ((float) j + (float) (offset.y * (int) Chunk::size) + tileMap.seedOffsetGold.y) *
                                tileMap.scaleGold.y) +
                         1.0f) * 0.5f;
                float noiseResultDirt =
                        (SimplexNoise::noise(
                                ((float) i + (float) (offset.x * (int) Chunk::size) + tileMap.seedOffsetDirt.x) *
                                tileMap.scaleDirt.x,
                                ((float) j + (float) (offset.y * (int) Chunk::size) + tileMap.seedOffsetDirt.y) *
                                tileMap.scaleDirt.y) +
                         1.0f) * 0.5f;
                if (noiseResult < 0.2f)
                    noiseLevel[i + j * Chunk::size] = 0;
                else if (noiseResultDirt < 0.1f) {
                    noiseLevel[i + j * Chunk::size] = 4;
                    noiseLevel[i + j * Chunk::size + Chunk::size * Chunk::size] = 4;
                } else if (noiseResultIron < 0.05f)
                    noiseLevel[i + j * Chunk::size] = 2;
                else if (noiseResultGold < 0.03f)
                    noiseLevel[i + j * Chunk::size] = 3;
                else if (noiseLevel[i + j * Chunk::size] == 0)
                    noiseLevel[i + j * Chunk::size] = 1;

            }
        }
    }

    if (!tileMap.addChunk(sf::Vector2u(4, 4), noiseLevel, offset.x, offset.y))
        return false;


    for (int i = offset.x * (int) Chunk::size; i < offset.x * (int) Chunk::size + (int) Chunk::size; ++i) {
        for (int j = -tileMap.terrainAmplitude; j < tileMap.terrainAmplitude + 1; j++) {
            if (tileMap.getTileType(i, j) == 4) {
                std::cout << "Placed: " << i << " " << j << std::endl;
                tileMap.setTile(i, j, 5);
                break;
            } else if (tileMap.getTileType(i, j) != 0) {
                break;
            }
        }
    }


    return true;
}
