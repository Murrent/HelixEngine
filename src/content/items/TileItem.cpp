#include <iostream>
#include "TileItem.hpp"
#include "../../scene/GameManager.hpp"

TileItem::TileItem() : Item(64) {
    tileType = 1;
}

TileItem::TileItem(Tile &tile) : Item(64) {
    tileType = tile.id;
    sprite.setTexture(GameManager::map.m_tileset);
    sprite.setTextureRect(tile.frames[0]);
    std::cout << sprite.getTextureRect().left << " "
              << sprite.getTextureRect().top << " "
              << sprite.getTextureRect().width << " "
              << sprite.getTextureRect().height << std::endl;
    name = tile.name;
    description = "A " + tile.name + " tile.";
}

void TileItem::Use() {

}

void TileItem::Use2() {

}

TileItem::~TileItem() {
    std::cout << "Destroyed tile: " + name << std::endl;
}
