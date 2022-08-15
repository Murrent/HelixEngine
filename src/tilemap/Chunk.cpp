#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <dirent.h>
#include <fstream>
#include "Chunk.hpp"
#include "../scene/GameManager.hpp"
#include "../common/Random.hpp"


bool Chunk::load(sf::Texture &tileset, int x, int y, const int *_tiles) {
    position.x = x;
    position.y = y;
    m_tileset = &tileset;
    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    b_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(size * size * 4);
    b_vertices.resize(size * size * 4);

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
            quad[0].position =
                    (sf::Vector2f) position * (float) size + 0.25f * sf::Vector2f((float) i * (float) spriteSize,
                                                                                  (float) j * (float) spriteSize);
            quad[1].position =
                    (sf::Vector2f) position * (float) size + 0.25f * sf::Vector2f((float) (i + 1) * (float) spriteSize,
                                                                                  (float) j * (float) spriteSize);
            quad[2].position =
                    (sf::Vector2f) position * (float) size + 0.25f * sf::Vector2f((float) (i + 1) * (float) spriteSize,
                                                                                  (float) (j + 1) * (float) spriteSize);
            quad[3].position =
                    (sf::Vector2f) position * (float) size + 0.25f * sf::Vector2f((float) i * (float) spriteSize,
                                                                                  (float) (j + 1) * (float) spriteSize);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(float(frame.left), float(frame.top));
            quad[1].texCoords = sf::Vector2f(float(frame.left + frame.width), float(frame.top));
            quad[2].texCoords = sf::Vector2f(float(frame.left + frame.width), float(frame.top + frame.height));
            quad[3].texCoords = sf::Vector2f(float(frame.left), float(frame.top + frame.height));
        }
    }

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = 0; j < size; ++j) {
            // get the current tile number
            unsigned int tileNumber = _tiles[i + j * size + size * size];
            backTiles[i][j] = tileNumber;
            unsigned int frameCount = GameManager::map.tileLookupTable[tileNumber].frames.size();
            unsigned int frameIndex = rngRangeU(0, frameCount);
            sf::IntRect frame = GameManager::map.tileLookupTable[tileNumber].frames[frameIndex];

            // get a pointer to the current tile's quad
            sf::Vertex *quad = &b_vertices[(i + j * size) * 4];

            // define its 4 corners
            // 1 tile will now be 1 * 1 in size
            quad[0].position =
                    (sf::Vector2f) position * (float) size + 0.25f * sf::Vector2f((float) i * (float) spriteSize,
                                                                                  (float) j * (float) spriteSize);
            quad[1].position =
                    (sf::Vector2f) position * (float) size + 0.25f * sf::Vector2f((float) (i + 1) * (float) spriteSize,
                                                                                  (float) j * (float) spriteSize);
            quad[2].position =
                    (sf::Vector2f) position * (float) size + 0.25f * sf::Vector2f((float) (i + 1) * (float) spriteSize,
                                                                                  (float) (j + 1) * (float) spriteSize);
            quad[3].position =
                    (sf::Vector2f) position * (float) size + 0.25f * sf::Vector2f((float) i * (float) spriteSize,
                                                                                  (float) (j + 1) * (float) spriteSize);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(float(frame.left), float(frame.top));
            quad[1].texCoords = sf::Vector2f(float(frame.left + frame.width), float(frame.top));
            quad[2].texCoords = sf::Vector2f(float(frame.left + frame.width), float(frame.top + frame.height));
            quad[3].texCoords = sf::Vector2f(float(frame.left), float(frame.top + frame.height));

            quad[0].color = sf::Color(200, 200, 200);
            quad[1].color = sf::Color(200, 200, 200);
            quad[2].color = sf::Color(200, 200, 200);
            quad[3].color = sf::Color(200, 200, 200);
        }
    }

    return true;
}

void Chunk::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the tileset texture
    states.texture = m_tileset;

//    // draw the vertex array
//    sf::Texture texture;
//    texture.update(m_vertices);
//    texture.clear(sf::Color::Blue);
//    texture.create(size * spriteSize, size * spriteSize);
//    texture.draw(m_vertices);
//    texture.display();
//
//    sf::Sprite sprite;
//    sprite.setTexture(texture.getTexture());
//    float scale = 1.0f / spriteSize;
//    sprite.setScale(scale, scale);
//    sprite.setPosition(getPosition());

    target.draw(b_vertices, states);
    target.draw(m_vertices, states);
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

    saveTile(x, y, tile);
}

void Chunk::setTileBack(unsigned int x, unsigned int y, unsigned int tile) {
    this->backTiles[x][y] = tile;
    // get a pointer to the current tile's quad
    sf::Vertex *quad = &b_vertices[(x + y * size) * 4];

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

unsigned int Chunk::getTileTypeBack(unsigned int x, unsigned int y) {
    return this->backTiles[x][y];
}

sf::Vector3i parseTileInfo(std::string &string) {
    sf::Vector3i outVec;
    std::string buffer;
    unsigned long long firstSep = string.find('_', 0);
    unsigned long long secondSep = string.find('_', 1);
    buffer = string.substr(0, firstSep);
    std::cout << buffer << std::endl;
    buffer = string.substr(firstSep, secondSep);
    std::cout << buffer << std::endl;
    buffer = string.substr(secondSep, string.size());
    std::cout << buffer << std::endl;
    return outVec;
}

void Chunk::writeTileToFile(unsigned int x, unsigned int y, unsigned int tile, const std::string &directory) {
    // load Tiles.conf and create tiles and add them to the lookup table
    std::string fullDir = directory + "/" + std::to_string(position.x) + "_" + std::to_string(position.y) + ".txt";
    std::string newTile = std::to_string(x) + '_' + std::to_string(y) + '_' + std::to_string(tile) + '\n';

    std::fstream fs;
    fs.open(fullDir, std::ios::in);

    std::string newString;
    bool foundSame = false;

    if (fs.good()) {
        std::cout << "Reading file: " << fullDir << std::endl;

        char *bytes = new char[1024];
        std::string string;
        while (!fs.eof()) {
            fs.getline(bytes, 1024);
            std::cout << "looping line : " << bytes << std::endl;
            string = std::string(bytes);
            if (!string.empty()) {
                sf::Vector3i tileInfo = parseTileInfo(string);
                if (tileInfo.x == x && tileInfo.y == y && tileInfo.z != tile) {
                    newString += newTile; // This doesnt seem to work, duplicated saved tile for same coordinate
                    foundSame = true;
                    break;
                }
            }
            if (string.find('\n') == -1)
                newString.append(string + '\n');
            else
                newString.append(string);
            std::cout << "loop adding: " << string << std::endl;
            std::cout << "loop: " << newString << std::endl;
        }
        //newString.pop_back();
        std::cout << "newString: " << newString.c_str() << std::endl;
        fs.close();
    } else {
        fs.close();
        std::ofstream createFile{fullDir};
        createFile.close();
    }

    if (!foundSame)
        newString += newTile;
    newString.pop_back();
    fs.open(fullDir, std::ios::out);
    fs << newString;


    fs.close();
}

void Chunk::saveTile(unsigned int x, unsigned int y, unsigned int tile) {

    std::cout << "saving tile" << std::endl;
    struct dirent *entry;
    std::string dirString = "../saves/";
    DIR *dir = opendir(dirString.c_str());

    if (dir == nullptr) {
        std::cout << "weird dir" << std::endl;
        return;
    }
    std::cout << std::endl;
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        size_t lastIndex = name.find_first_of('.');
        std::string rawName = name.substr(0, lastIndex);
        if (rawName.length() != 0) {
            if (rawName == GameManager::map.worldName) {
                std::cout << rawName << " was found" << std::endl;
                writeTileToFile(x, y, tile, dirString + GameManager::map.worldName);

                closedir(dir);
                return;
            }

            std::cout << rawName << std::endl;
        }
    }
//    if (mkdir((dirString + GameManager::map.worldName).c_str()) == -1) {
//        std::cout << "Failed to create directory: " << GameManager::map.worldName << std::endl;
//
//        writeTileToFile(x, y, tile, dirString + GameManager::map.worldName);
//    } else {
//        std::cout << "Created directory: " << GameManager::map.worldName << std::endl;
//
//        writeTileToFile(x, y, tile, dirString + GameManager::map.worldName);
//    }
    closedir(dir);
}
