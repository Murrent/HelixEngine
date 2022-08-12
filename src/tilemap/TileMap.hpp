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
    unsigned int seed;
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

    //std::unordered_map<int, std::unordered_map<int, Chunk>> chunks;
};

