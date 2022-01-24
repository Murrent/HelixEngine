//
// Created by Martin on 2021-01-01.
//

#include "Chunk.h"

Chunk::Chunk(sf::Vector2i _offset) {
    offset = _offset;
}

void Chunk::SetTile(Tile *tile, sf::Texture &texture) {
    tile->sprite.setTexture(texture);
    tile->draw = true;
}

void Chunk::SetTile(sf::Vector2i pos, sf::Texture &texture) {
    tiles[pos.x][pos.y].sprite.setTexture(texture);
    tiles[pos.x][pos.y].draw = true;
}

void Chunk::SetTile(int x, int y, sf::Texture &texture) {
    tiles[x][y].sprite.setTexture(texture);
    tiles[x][y].draw = true;
}

void Chunk::RemoveTile(Tile *tile) {
    tile->draw = false;
}

void Chunk::RemoveTile(sf::Vector2i pos) {
    tiles[pos.x][pos.y].draw = false;
}

void Chunk::RemoveTile(int x, int y) {
    tiles[x][y].draw = false;
}

Tile *Chunk::GetTile(sf::Vector2i pos) {
    return &tiles[pos.x][pos.y];
}

Tile *Chunk::GetTile(int x, int y) {
    return &tiles[x][y];
}

bool Chunk::ShouldDraw(Tile *tile) {
    return tile->draw;

}

bool Chunk::ShouldDraw(sf::Vector2i pos) {
    return tiles[pos.x][pos.y].draw;
}

bool Chunk::ShouldDraw(int x, int y) {
    return tiles[x][y].draw;
}

void Chunk::Draw(sf::RenderTarget &renderTarget) {
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            renderTarget.draw(tiles[x][y].sprite);
        }
    }
}

void Chunk::Fill(sf::Texture &texture) {
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            SetTile(x, y, texture);
            tiles[x][y].sprite.setScale(5, 5);
            tiles[x][y].sprite.setPosition(
                    offset.x * size * tiles[x][y].sprite.getTextureRect().width * tiles[x][y].sprite.getScale().x +
                    x * tiles[x][y].sprite.getTextureRect().width * tiles[x][y].sprite.getScale().x,
                    offset.y * size * tiles[x][y].sprite.getTextureRect().height * tiles[x][y].sprite.getScale().y +
                    y * tiles[x][y].sprite.getTextureRect().height * tiles[x][y].sprite.getScale().y);
        }
    }
}
