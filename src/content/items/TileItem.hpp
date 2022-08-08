#pragma once


#include "Item.hpp"
#include "../../tilemap/Chunk.hpp"

class TileItem : public Item {
public:
    unsigned int tileType;

    TileItem();

    explicit TileItem(Tile &tile);

    void Use() override;

    void Use2() override;

    ~TileItem() override;
};

