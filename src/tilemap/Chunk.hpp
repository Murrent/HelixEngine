#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Chunk : public sf::Drawable, public sf::Transformable {
public:

    static constexpr unsigned int size = 16;
    static constexpr unsigned int spriteSize = 4;

    bool load(sf::Texture &tileset, sf::Vector2u tileSize, const int *tiles);

    void setTile(unsigned int x, unsigned int y, unsigned int tile);

    unsigned int getTileType(unsigned int x, unsigned int y);
private:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    unsigned int tiles[size][size];

    sf::VertexArray m_vertices;
    sf::Texture *m_tileset;
};

