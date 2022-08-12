#include <cmath>
#include "PickaxeIron.hpp"
#include "../../scene/GameManager.hpp"
#include "TileItem.hpp"
#include "../../common/Random.hpp"

PickaxeIron::PickaxeIron() {
    this->sprite.setTexture(GameManager::resources.textures["pickaxe_iron"]);
}

void PickaxeIron::Use() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(GameManager::window);
    sf::Vector2f worldPos = GameManager::window.mapPixelToCoords(mousePos);
    sf::Vector2i tilePos = sf::Vector2i(std::floor(worldPos.x), std::floor(worldPos.y));
    unsigned int tileType = GameManager::map.getTileType(tilePos.x, tilePos.y);
    if (tileType != 0) {
        GameManager::map.setTile(tilePos.x, tilePos.y, 0);
        auto *tile = new TileItem(GameManager::map.tileLookupTable[tileType]);
        GameManager::physicsManager.addItem(tile, (float) tilePos.x + 0.5f, (float) tilePos.y + 0.5f,
                                            rngRangeF(-0.5f, 0.5f), rngRangeF(-0.2f, -1.0f));
    }
}

void PickaxeIron::Use2() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(GameManager::window);
    sf::Vector2f worldPos = GameManager::window.mapPixelToCoords(mousePos);
    sf::Vector2i tilePos = sf::Vector2i(std::floor(worldPos.x), std::floor(worldPos.y));
    unsigned int tileType = GameManager::map.getTileTypeBack(tilePos.x, tilePos.y);
    if (tileType != 0) {
        GameManager::map.setTileBack(tilePos.x, tilePos.y, 0);
        auto *tile = new TileItem(GameManager::map.tileLookupTable[tileType]);
        GameManager::physicsManager.addItem(tile, (float) tilePos.x + 0.5f, (float) tilePos.y + 0.5f,
                                            rngRangeF(-0.5f, 0.5f), rngRangeF(-0.2f, -1.0f));
    }
}
