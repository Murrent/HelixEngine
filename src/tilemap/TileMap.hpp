#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Chunk.hpp"

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool setTileset(const std::string &tileset);

    bool addChunk(sf::Vector2u tileSize, const int *tiles, int x, int y);

    void setTile(int x, int y, unsigned int tile);

    unsigned int getTileType(int x, int y);

    unsigned int getTileType(float x, float y);

    void removeChunk(sf::Vector2i);
private:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    //std::vector<Chunk> chunks;
    std::unordered_map<int, std::unordered_map<int, Chunk>> chunks;
    sf::Texture m_tileset;
};

