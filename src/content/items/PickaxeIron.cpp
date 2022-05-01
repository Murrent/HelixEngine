#include <cmath>
#include "PickaxeIron.hpp"
#include "../../scene/GameManager.hpp"

PickaxeIron::PickaxeIron() {
    this->sprite.setTexture(GameManager::textures.textures["pickaxe_iron"]);
}

void PickaxeIron::Use() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(GameManager::window);
    sf::Vector2f worldPos = GameManager::window.mapPixelToCoords(mousePos);
    GameManager::map.setTile(std::floor(worldPos.x), std::floor(worldPos.y), 0);
}

void PickaxeIron::Use2() {

}
