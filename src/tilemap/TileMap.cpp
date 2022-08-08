
#include <iostream>
#include <string>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cmath>
#include <SFML/System/InputStream.hpp>
#include <fstream>
#include "TileMap.hpp"

void getNextConfigElement(std::string &string, std::string &buffer, char separator, unsigned long long &index) {
    unsigned long long endPos = string.find(separator, index);
    if (endPos == std::string::npos) {
        buffer = string.substr(index, string.size());
        index = std::string::npos;
        return;
    }
    buffer = string.substr(index, endPos - index);
    index = endPos + 1;
}

Tile TileMap::createTile(std::string &string) {
    unsigned long long index = 0;
    std::string buffer;

    Tile tile;

    tile.id = tileLookupTable.size();

    // The tile name
    getNextConfigElement(string, buffer, ',', index);
    tile.name = buffer;

    // The collider type
    getNextConfigElement(string, buffer, ',', index);
    if (buffer == "RECTANGLE")
        tile.colliderType = ColliderType::SQUARE;
    else
        tile.colliderType = ColliderType::NONE;

    // The animate bool
    getNextConfigElement(string, buffer, ',', index);
    if (buffer == "0")
        tile.animate = false;
    else
        tile.animate = true;

    // The choseRandom bool
    getNextConfigElement(string, buffer, ',', index);
    if (buffer == "0")
        tile.choseRandom = false;
    else
        tile.choseRandom = true;

    // Size of the tile
    getNextConfigElement(string, buffer, ',', index);
    std::string strX = buffer.substr(0, buffer.find('-'));
    std::string strY = buffer.substr(buffer.find('-') + 1, buffer.size());
    unsigned int intX = std::stoi(strX);
    unsigned int intY = std::stoi(strY);
    tile.size = sf::Vector2u(intX, intY);

    // The frames of the tile
    while (index != std::string::npos) {
        getNextConfigElement(string, buffer, ',', index);
        sf::IntRect rect;
        unsigned long long rectIndex = 0;
        std::string intBuf;

        getNextConfigElement(buffer, intBuf, '-', rectIndex);
        rect.left = std::stoi(intBuf);
        getNextConfigElement(buffer, intBuf, '-', rectIndex);
        rect.top = std::stoi(intBuf);
        getNextConfigElement(buffer, intBuf, '-', rectIndex);
        rect.width = std::stoi(intBuf);
        getNextConfigElement(buffer, intBuf, '-', rectIndex);
        rect.height = std::stoi(intBuf);

        tile.frames.emplace_back(rect);
    }
    return tile;
}

bool TileMap::setTileset(const std::string &tileset) {
    // load Tiles.conf and create tiles and add them to the lookup table
    std::fstream fs;
    fs.open("../assets/sprites/Tiles.conf", std::ios::in);
    if (!fs) {
        printf("Failed to locate Tiles.conf\n");
        return false;
    }

    char *bytes = new char[1024];
    while (!fs.eof()) {
        fs.getline(bytes, 1024);
        std::string string(bytes);
        tileLookupTable.emplace_back(createTile(string));
    }

    fs.close();

    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    return true;
}

bool TileMap::addChunk(sf::Vector2u tileSize, const int *tiles, int x, int y) {
    Chunk chunk;
    chunk.setPosition((float) (x) * Chunk::size, (float) (y) * Chunk::size);
    if (chunk.load(m_tileset, x, y, tiles)) {
        chunks.push_back(chunk);
        return true;
    } else
        return false;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &i: chunks) {
        target.draw(i);
    }
}

void TileMap::setTile(int x, int y, unsigned int tile) {
    sf::Vector2i chunkPos(std::floor(float(x) / float(Chunk::size)), std::floor(float(y) / float(Chunk::size)));
    //std::cout << chunkPos.x << " " << chunkPos.y << std::endl;
    for (auto &chunk : chunks) {
        if (chunk.position == chunkPos) {
            chunk.setTile(x - chunkPos.x * (int) Chunk::size,
                          y - chunkPos.y * (int) Chunk::size, tile);
            return;
        }
    }
}

void TileMap::setTile(int x, int y, const std::string &tileName) {
    for (int i = 0; i < tileLookupTable.size(); i++) {
        if (tileLookupTable[i].name == tileName)
            setTile(x, y, i);
    }
}

void TileMap::removeChunk(sf::Vector2i pos) {
    for (int i = 0; i < chunks.size(); i++) {
        auto &chunk = chunks[i];
        if (chunk.position == pos) {
            chunks.erase(chunks.begin() + i);
        }
    }
//    auto gotX = chunks.find(pos.x);
//    if (gotX != chunks.end()) {
//        auto gotY = chunks[pos.x].find(pos.y);
//        if (gotY != chunks[pos.x].end()) {
//            chunks[pos.x].erase(pos.y);
//            if (chunks[pos.x].empty())
//                chunks.erase(pos.x);
//        }
//    }
}

unsigned int TileMap::getTileType(int x, int y) {
    sf::Vector2i chunkPos(std::floor(float(x) / float(Chunk::size)), std::floor(float(y) / float(Chunk::size)));
    for (auto &chunk : chunks) {
        if (chunk.position == chunkPos) {
            return chunk.getTileType(x - chunkPos.x * (int) Chunk::size,
                                     y - chunkPos.y * (int) Chunk::size);
        }
    }
//    auto gotX = chunks.find(chunkPos.x);
//    if (gotX != chunks.end()) {
//        auto gotY = chunks[chunkPos.x].find(chunkPos.y);
//        if (gotY != chunks[chunkPos.x].end()) {
//            return chunks[chunkPos.x][chunkPos.y].getTileType(x - chunkPos.x * (int) Chunk::size,
//                                                              y - chunkPos.y * (int) Chunk::size);
//        }
//    }
    return 0;
}

unsigned int TileMap::getTileType(float x, float y) {
    return this->getTileType(int(std::floor(x)), int(std::floor(y)));
}

