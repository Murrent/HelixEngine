//
// Created by martin on 2021-06-15.
//

#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "Chunk.hpp"

bool Chunk::load(sf::Texture &tileset, sf::Vector2u tileSize, const int *_tiles) {
    m_tileset = &tileset;
    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(size * size * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < size; ++i)
        for (unsigned int j = 0; j < size; ++j) {
            // get the current tile number
            unsigned int tileNumber = _tiles[i + j * size];
            this->tiles[i][j] = tileNumber;

            // find its position in the tileset texture
            unsigned int tu = tileNumber % (tileset.getSize().x / tileSize.x);
            unsigned int tv = tileNumber / (tileset.getSize().x / tileSize.x);
            //std::cout << tu << " " << tv << std::endl;
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
            quad[0].texCoords = sf::Vector2f((float) tu * (float) tileSize.x,
                                             (float) tv * (float) tileSize.y);
            quad[1].texCoords = sf::Vector2f((float) (tu + 1) * (float) tileSize.x,
                                             (float) tv * (float) tileSize.y);
            quad[2].texCoords = sf::Vector2f((float) (tu + 1) * (float) tileSize.x,
                                             (float) (tv + 1) * (float) tileSize.y);
            quad[3].texCoords = sf::Vector2f((float) tu * (float) tileSize.x,
                                             (float) (tv + 1) * (float) tileSize.y);


        }

    return true;
}

void Chunk::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
    //states.transform *= getTransform();

    // apply the tileset texture
    states.texture = m_tileset;

    // draw the vertex array
    sf::RenderTexture renderTexture;
    renderTexture.create(size * spriteSize, size * spriteSize);
    renderTexture.clear(sf::Color::Blue);

    renderTexture.draw(m_vertices, states);
    renderTexture.display();

    sf::Sprite sprite(renderTexture.getTexture());
    float scale = 1.0f / spriteSize;
    sprite.setScale(scale, scale);
    sprite.setPosition(getPosition());

    target.draw(sprite);
}

void Chunk::setTile(unsigned int x, unsigned int y, unsigned int tile) {
    this->tiles[x][y] = tile;
    // find its position in the tileset texture
    unsigned int tu = tile % (m_tileset->getSize().x / spriteSize);
    unsigned int tv = tile / (m_tileset->getSize().x / spriteSize);
    //std::cout << tu << " " << tv << std::endl;
    // get a pointer to the current tile's quad
    sf::Vertex *quad = &m_vertices[(x + y * size) * 4];

    // define its 4 texture coordinates
    quad[0].texCoords = sf::Vector2f((float) tu * (float) spriteSize,
                                     (float) tv * (float) spriteSize);
    quad[1].texCoords = sf::Vector2f((float) (tu + 1) * (float) spriteSize,
                                     (float) tv * (float) spriteSize);
    quad[2].texCoords = sf::Vector2f((float) (tu + 1) * (float) spriteSize,
                                     (float) (tv + 1) * (float) spriteSize);
    quad[3].texCoords = sf::Vector2f((float) tu * (float) spriteSize,
                                     (float) (tv + 1) * (float) spriteSize);
}

unsigned int Chunk::getTileType(unsigned int x, unsigned int y) {
    return this->tiles[x][y];
}
