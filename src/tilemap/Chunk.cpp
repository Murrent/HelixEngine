#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include "Chunk.hpp"
#include "../scene/GameManager.hpp"
#include "../common/Random.hpp"

bool Chunk::load(sf::Texture &tileset, sf::Vector2u tileSize, const int *_tiles) {
    m_tileset = &tileset;
    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(size * size * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = 0; j < size; ++j) {
            // get the current tile number
            unsigned int tileNumber = _tiles[i + j * size];
            tiles[i][j] = tileNumber;
            unsigned int frameCount = GameManager::map.tileLookupTable[tileNumber].frames.size();
            unsigned int frameIndex = rngRangeU(0, frameCount);
            sf::IntRect frame = GameManager::map.tileLookupTable[tileNumber].frames[frameIndex];

            // get a pointer to the current tile's quad
            sf::Vertex *quad = &m_vertices[(i + j * size) * 4];

            // define its 4 corners
            // 1 tile will now be 1 * 1 in size
            quad[0].position = sf::Vector2f((float) i * (float) tileSize.x,
                                            (float) j * (float) tileSize.y);
            quad[1].position = sf::Vector2f((float) (i + 1) * (float) tileSize.x,
                                            (float) j * (float) tileSize.y);
            quad[2].position = sf::Vector2f((float) (i + 1) * (float) tileSize.x,
                                            (float) (j + 1) * (float) tileSize.y);
            quad[3].position = sf::Vector2f((float) i * (float) tileSize.x,
                                            (float) (j + 1) * (float) tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(float(frame.left), float(frame.top));
            quad[1].texCoords = sf::Vector2f(float(frame.left + frame.width), float(frame.top));
            quad[2].texCoords = sf::Vector2f(float(frame.left + frame.width), float(frame.top + frame.height));
            quad[3].texCoords = sf::Vector2f(float(frame.left), float(frame.top + frame.height));
        }
    }

    return true;
}

void Chunk::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the tileset texture
    states.texture = m_tileset;

    // draw the vertex array
    sf::RenderTexture texture;
    texture.create(size * spriteSize, size * spriteSize);
    texture.clear(sf::Color::Blue);

    texture.draw(m_vertices, states);
    texture.display();

    sf::Sprite sprite;
    sprite.setTexture(texture.getTexture());
    float scale = 1.0f / spriteSize;
    sprite.setScale(scale, scale);
    sprite.setPosition(getPosition());

    target.draw(sprite);
}

void Chunk::setTile(unsigned int x, unsigned int y, unsigned int tile) {
    this->tiles[x][y] = tile;
    // get a pointer to the current tile's quad
    sf::Vertex *quad = &m_vertices[(x + y * size) * 4];

    unsigned int frameCount = GameManager::map.tileLookupTable[tile].frames.size();
    unsigned int frameIndex = rngRangeU(0, frameCount);
    sf::IntRect frame = GameManager::map.tileLookupTable[tile].frames[frameIndex];

    quad[0].texCoords = sf::Vector2f(float(frame.left), float(frame.top));
    quad[1].texCoords = sf::Vector2f(float(frame.left + frame.width), float(frame.top));
    quad[2].texCoords = sf::Vector2f(float(frame.left + frame.width), float(frame.top + frame.height));
    quad[3].texCoords = sf::Vector2f(float(frame.left), float(frame.top + frame.height));
}

unsigned int Chunk::getTileType(unsigned int x, unsigned int y) {
    return this->tiles[x][y];
}

