#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <unordered_map>
#include "Chunk.hpp"

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    std::string worldName;
    // Noise parameters
    unsigned int seed;
    sf::Vector2f scaleHeight{0, 0};
    sf::Vector2f seedOffsetHeight{0, 0};
    sf::Vector2f scaleCave{0, 0};
    sf::Vector2f seedOffsetCave{0, 0};
    sf::Vector2f scaleIron{0, 0};
    sf::Vector2f seedOffsetIron{0, 0};
    sf::Vector2f scaleGold{0, 0};
    sf::Vector2f seedOffsetGold{0, 0};
    sf::Vector2f scaleDirt{0, 0};
    sf::Vector2f seedOffsetDirt{0, 0};
    int terrainAmplitude = 0.0f;

    std::vector<Tile> tileLookupTable;
    sf::Texture m_tileset;


    bool setTileset(const std::string &tileset);

    bool addChunk(sf::Vector2u tileSize, const int *tiles, int x, int y);

    void setTile(int x, int y, unsigned int tile);

    void setTileBack(int x, int y, unsigned int tile);

    void setTile(int x, int y, const std::string &tile);

    void setTileBack(int x, int y, const std::string &tile);

    unsigned int getTileType(int x, int y);

    unsigned int getTileTypeBack(int x, int y);

    unsigned int getTileType(float x, float y);

    unsigned int getTileTypeBack(float x, float y);

    void removeChunk(sf::Vector2i);

    bool chunkExists(int x, int y);

private:
    Tile createTile(std::string &string);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    std::vector<Chunk> chunks;
};

