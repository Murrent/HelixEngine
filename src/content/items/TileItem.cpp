#include <iostream>
#include <cmath>
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
    sf::Vector2i mousePos = sf::Mouse::getPosition(GameManager::window);
    sf::Vector2f worldPos = GameManager::window.mapPixelToCoords(mousePos);
    sf::Vector2i tilePos = sf::Vector2i(std::floor(worldPos.x), std::floor(worldPos.y));
    if (GameManager::map.getTileType(tilePos.x, tilePos.y) == 0) {
        GameManager::map.setTile(tilePos.x, tilePos.y, tileType);
        amount--;
        if (amount == 0)
        {
            GameManager::player.inventory.removeItem(this);
            delete this;
        }
    }
}

void TileItem::Use2() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(GameManager::window);
    sf::Vector2f worldPos = GameManager::window.mapPixelToCoords(mousePos);
    sf::Vector2i tilePos = sf::Vector2i(std::floor(worldPos.x), std::floor(worldPos.y));
    if (GameManager::map.getTileTypeBack(tilePos.x, tilePos.y) == 0) {
        GameManager::map.setTileBack(tilePos.x, tilePos.y, tileType);
        amount--;
        if (amount == 0)
        {
            GameManager::player.inventory.removeItem(this);
            delete this;
        }
    }
}

TileItem::~TileItem() {
    std::cout << "Destroyed tile: " + name << std::endl;
}
