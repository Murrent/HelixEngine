//
// Created by Martin on 2021-01-18.
//

#ifndef GAMEENGINE_CHUNKHANDLER_H
#define GAMEENGINE_CHUNKHANDLER_H

#include <unordered_map>
#include <SFML/System/Vector2.hpp>
#include "Chunk.h"

class ChunkHandler {
private:
    std::unordered_map<int, std::unordered_map<int, Chunk*>> chunks;
public:
    void AddChunk(sf::Vector2i pos, sf::Texture& texture);
    void RemoveChunk(sf::Vector2i);
    void Draw(sf::RenderTarget& renderTarget);
};


#endif //GAMEENGINE_CHUNKHANDLER_H
