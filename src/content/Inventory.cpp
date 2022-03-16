#include "Inventory.hpp"
#include "../scene/GameManager.hpp"

std::vector<Item *> Inventory::getItems() {
    std::vector<Item *> itemVector;
    for (auto &column : this->items) {
        for (auto &item : column) {
            if (item != nullptr)
                itemVector.push_back(item);
        }
    }
    return itemVector;
}

void Inventory::setSize(unsigned int x, unsigned int y) {
    this->background.setSize(sf::Vector2f((float) x, (float) y));
    this->background.setOrigin(sf::Vector2f((float) x, (float) y) * 0.5f);
    // Store all current items
    std::vector<Item *> prevItems = this->getItems();
    // resize
    this->items.resize(x);
    for (auto &column : this->items) {
        column.resize(y);
    }

    // Store all pointers again and check if they don't exist in the new array we drop it on the ground to not get memory leak
    for (auto &column : this->items) {
        for (auto &item : column) {
            if (item != nullptr) {
                for (auto &prevItem : prevItems) {
                    if (item == prevItem) {
                        prevItem = nullptr;
                    }
                }
            }
        }
    }

    for (auto &prevItem : prevItems) {
        delete (prevItem);
        // Spawn it in the world if it's not null (deleting until item spawning is implemented)
    }
}

bool Inventory::addItem(Item *item) {
    for (auto &column : this->items) {
        for (auto &slot : column) {
            if (slot == nullptr) {
                slot = item;
                return true;
            }
        }
    }
    return false;
}

bool Inventory::addItemToSlot(sf::Vector2u pos, Item *item) {
    if (items.size() - 1 <= pos.x && items[pos.x].size() - 1 <= pos.y && items[pos.x][pos.y] != nullptr) {
        items[pos.x][pos.y] = item;
        return true;
    }
    return false;
}

Item *Inventory::removeItem(sf::Vector2u pos) {
    if (items.size() - 1 <= pos.x && items[pos.x].size() - 1 <= pos.y && items[pos.x][pos.y] != nullptr) {
        Item *item = items[pos.x][pos.y];
        items[pos.x][pos.y] = nullptr;
        return item;
    }
    return nullptr;
}

void Inventory::start() {
    Entity::start();
    this->background.setPosition(0.0f, 0.0f);
}

void Inventory::update() {
    Entity::update();
}

void Inventory::draw() {
    Entity::draw();
    sf::View oldView = GameManager::window.getView();
    sf::View tmpView(sf::Vector2f(0, 0), (sf::Vector2f)GameManager::window.getSize());
    float scale = tmpView.getSize().y * 0.08f;
    this->background.setScale(scale, scale);
    GameManager::window.setView(tmpView);
    GameManager::window.draw(this->background);

    for (int x = 0; x < this->items.size(); x++) {
        for (int y = 0; y < this->items[x].size(); y++) {
            sf::RectangleShape rect;
            rect.setOrigin(this->background.getSize() * scale * 0.5f);
            rect.setFillColor(sf::Color::Magenta);
            rect.setSize(sf::Vector2f(0.9f, 0.9f) * scale);
            rect.setPosition((0.05f + x) * scale, (0.05f + y) * scale);
            GameManager::window.draw(rect);
        }
    }

    GameManager::window.setView(oldView);
}


