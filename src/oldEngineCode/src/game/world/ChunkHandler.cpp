//
// Created by Martin on 2021-01-18.
//

#include "ChunkHandler.h"

void ChunkHandler::AddChunk(sf::Vector2i pos, sf::Texture& texture) {
    auto* chunk = new Chunk(pos);
    chunk->Fill(texture);
    chunks[pos.x][pos.y] = chunk;
}

void ChunkHandler::RemoveChunk(sf::Vector2i pos) {
    auto gotX = chunks.find(pos.x);
    if (gotX != chunks.end()) {
        auto gotY = chunks[pos.x].find(pos.y);
        if (gotY != chunks[pos.x].end()) {
            free(chunks[pos.x][pos.y]);
            chunks[pos.x].erase(pos.y);
            if (chunks[pos.x].empty())
                chunks.erase(pos.x);
        }
    }
}

void ChunkHandler::Draw(sf::RenderTarget &renderTarget) {
    for ( auto& x: chunks ){
        for ( auto& y: x.second ) {
            y.second->Draw(renderTarget);
        }
    }
}
