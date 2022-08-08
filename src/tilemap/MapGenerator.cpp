#include "MapGenerator.hpp"
#include "../noise/SimplexNoise.hpp"
#include "../common/Random.hpp"

bool MapGenerator::initialGeneration(TileMap &tileMap, const std::string &tileset) {
    rngRefreshSeed();

    if (!tileMap.setTileset(tileset))
        return false;

    int noiseLevel[Chunk::size * Chunk::size];
    sf::Vector2i offset(0, 0);
    sf::Vector2f scaleHeight(0.03f, 0.03f);
    sf::Vector2f seedOffsetHeight(0, 0);
    sf::Vector2f scaleCave(0.03f, 0.03f);
    sf::Vector2f seedOffsetCave(0, 0);
    sf::Vector2f scaleIron(0.03f, 0.03f);
    sf::Vector2f seedOffsetIron(5000, 5000);
    sf::Vector2f scaleGold(0.03f, 0.03f);
    sf::Vector2f seedOffsetGold(100, 100);
    sf::Vector2f scaleDirt(0.03f, 0.03f);
    sf::Vector2f seedOffsetDirt(1000, 1000);
    int terrainAmplitude = 10.0f;
    for (int x = -5; x < 5; ++x) {
        offset.x = x;
        for (int y = -4; y < 3; ++y) {
            offset.y = y;
            for (int i = 0; i < Chunk::size; i++) {
                for (int j = 0; j < Chunk::size; j++) {
                    noiseLevel[i + j * Chunk::size] = 0;
                    float heightNoise = SimplexNoise::noise(
                            ((float) i + (float) (offset.x * (int) Chunk::size) + seedOffsetHeight.x) * scaleHeight.x) *
                                        (float) terrainAmplitude;
                    float height = (float) j + (float) (offset.y * (int) Chunk::size);
                    if (heightNoise > height) {
                        noiseLevel[i + j * Chunk::size] = 0;
                    } else {
                        if (std::ceil(heightNoise) == std::ceil(height)) {
                            noiseLevel[i + j * Chunk::size] = 5;
                        } else if (heightNoise > height - 10) {
                            noiseLevel[i + j * Chunk::size] = 4;
                        }
                        float noiseResult =
                                (SimplexNoise::noise(
                                        ((float) i + (float) (offset.x * (int) Chunk::size) + seedOffsetCave.x) *
                                        scaleCave.x,
                                        ((float) j + (float) (offset.y * (int) Chunk::size) + seedOffsetCave.y) *
                                        scaleCave.y) +
                                 1.0f) * 0.5f;
                        float noiseResultIron =
                                (SimplexNoise::noise(
                                        ((float) i + (float) (offset.x * (int) Chunk::size) + seedOffsetIron.x) *
                                        scaleIron.x,
                                        ((float) j + (float) (offset.y * (int) Chunk::size) + seedOffsetIron.y) *
                                        scaleIron.y) +
                                 1.0f) * 0.5f;
                        float noiseResultGold =
                                (SimplexNoise::noise(
                                        ((float) i + (float) (offset.x * (int) Chunk::size) + seedOffsetGold.x) *
                                        scaleGold.x,
                                        ((float) j + (float) (offset.y * (int) Chunk::size) + seedOffsetGold.y) *
                                        scaleGold.y) +
                                 1.0f) * 0.5f;
                        float noiseResultDirt =
                                (SimplexNoise::noise(
                                        ((float) i + (float) (offset.x * (int) Chunk::size) + seedOffsetDirt.x) *
                                        scaleDirt.x,
                                        ((float) j + (float) (offset.y * (int) Chunk::size) + seedOffsetDirt.y) *
                                        scaleDirt.y) +
                                 1.0f) * 0.5f;
                        if (noiseResult < 0.2f)
                            noiseLevel[i + j * Chunk::size] = 0;
                        else if (noiseResultDirt < 0.1f)
                            noiseLevel[i + j * Chunk::size] = 4;
                        else if (noiseResultIron < 0.05f)
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
        }
    }
    for (int x = -5 * (int) Chunk::size; x < 5 * (int) Chunk::size; ++x) {
        for (int y = -terrainAmplitude; y < terrainAmplitude + 1; y++) {
            if ((tileMap.getTileType(x, y) == 4 || tileMap.getTileType(x, y) == 5) &&
                tileMap.getTileType(x, y - 1) == 0) {
                tileMap.setTile(x, y, 5);
                break;
            }
        }
    }

    return true;
}
