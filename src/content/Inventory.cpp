#include "Inventory.hpp"

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

bool Inventory::dropItem(sf::Vector2u pos) {
    if (items.size() - 1 <= pos.x && items[pos.x].size() - 1 <= pos.y && items[pos.x][pos.y] != nullptr) {
        delete (items[pos.x][pos.y]);
        items[pos.x][pos.y] = nullptr;
        return true;
    }
    return false;
}

