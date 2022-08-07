#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>


enum ColliderType {
    NONE,
    SQUARE
};

class Tile {
public:
    std::string name;
    ColliderType colliderType = SQUARE;
    bool animate, choseRandom;
    sf::Vector2u size = {1,1};
    // Sound effect
    // Particle effect
    std::vector<sf::IntRect> frames;
};

// One large spritesheet for tilemap sprites, with solid blocks, slopes, animated tiles, chests etc...
// chunk has an array of texture integers, and vector of animated tiles, so we easily can loop through and update them.
// Maybe have one array of tiles that point to tileinfotable so that multiple animation frames correspond to a single tile


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

    std::vector<sf::Vector2u> animatedTiles;

    std::vector<sf::Sprite> multiTileSprites;
    sf::VertexArray m_vertices;
    sf::Texture *m_tileset;
};

