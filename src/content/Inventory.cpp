#include "Inventory.hpp"
#include "../scene/GameManager.hpp"
#include "../system/Input.hpp"

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
    dimensions.x = x;
    dimensions.y = y;
    // Store all current items
    std::vector<Item *> prevItems = this->getItems();
    // resize
    this->items.resize(y);
    for (auto &column : this->items) {
        column.resize(x);
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
    if (items.size() - 1 <= pos.y && items[pos.y].size() - 1 <= pos.x && items[pos.y][pos.x] != nullptr) {
        items[pos.y][pos.x] = item;
        return true;
    }
    return false;
}

Item *Inventory::removeItem(sf::Vector2u pos) {
    if (items.size() - 1 <= pos.y && items[pos.y].size() - 1 <= pos.x && items[pos.y][pos.x] != nullptr) {
        Item *item = items[pos.y][pos.x];
        items[pos.y][pos.x] = nullptr;
        return item;
    }
    return nullptr;
}

void Inventory::start() {
    Entity::start();
    this->background.setPosition(0.0f, 0.0f);
    this->background.setFillColor(sf::Color(100, 100, 100));
}

void Inventory::update() {
    Entity::update();
    float scale = (float) GameManager::window.getSize().y * 0.08f;
    sf::Vector2i mousePos = sf::Mouse::getPosition(GameManager::window);
    sf::Vector2f origin =
            (sf::Vector2f) GameManager::window.getSize() * 0.5f - this->background.getSize() * scale * 0.5f;

    Item *hoverItem = nullptr;


    if (selected) {
        this->items[selectedPos.y][selectedPos.x]->sprite.setColor(sf::Color::Green);
        this->items[selectedPos.y][selectedPos.x]->sprite.setPosition((sf::Vector2f) mousePos - (sf::Vector2f) GameManager::window.getSize() * 0.5f);
        if (Input::input.getEvent(TRIGGER).getUp()) {
            selected = false;
            for (int y = 0; y < this->items.size(); y++) {
                for (int x = 0; x < this->items[y].size(); x++) {
                    sf::Rect rect(origin.x + (0.05f + x) * scale,
                                  origin.y + (0.05f + y) * scale,
                                  0.9f * scale,
                                  0.9f * scale);
                    if (this->items[y][x] == nullptr) {
                        if (rect.contains((sf::Vector2f) mousePos)) {
                            this->items[y][x] = this->items[selectedPos.y][selectedPos.x];
                            this->items[selectedPos.y][selectedPos.x] = nullptr;
                        }
                    }
                }
            }
        }
    } else {
        for (int y = 0; y < this->items.size(); y++) {
            for (int x = 0; x < this->items[y].size(); x++) {
                sf::Rect rect(origin.x + (0.05f + x) * scale, origin.y + (0.05f + y) * scale, 0.9f * scale,
                              0.9f * scale);
                if (this->items[y][x] != nullptr) {
                    if (rect.contains((sf::Vector2f) mousePos)) {
                        if (Input::input.getEvent(TRIGGER).getDown()) {
                            selected = true;
                            selectedPos.y = y;
                            selectedPos.x = x;
                        } else {
                            this->items[y][x]->sprite.setColor(sf::Color::Magenta);
                        }
                    } else
                        this->items[y][x]->sprite.setColor(sf::Color::White);
                }
            }
        }
    }
}

void Inventory::draw() {
    Entity::draw();
    sf::View oldView = GameManager::window.getView();
    sf::View tmpView(sf::Vector2f(0, 0), (sf::Vector2f) GameManager::window.getSize());
    float scale = tmpView.getSize().y * 0.08f;
    this->background.setScale(scale, scale);
    GameManager::window.setView(tmpView);
    GameManager::window.draw(this->background);

    for (int y = 0; y < this->items.size(); y++) {
        for (int x = 0; x < this->items[y].size(); x++) {
            sf::RectangleShape rect;
            rect.setOrigin(this->background.getSize() * scale * 0.5f);
            rect.setFillColor(sf::Color(80, 80, 80));
            rect.setSize(sf::Vector2f(0.9f, 0.9f) * scale);
            rect.setPosition((0.05f + x) * scale, (0.05f + y) * scale);
            GameManager::window.draw(rect);
        }
    }

    for (int y = 0; y < this->items.size(); y++) {
        for (int x = 0; x < this->items[y].size(); x++) {
            if (this->items[y][x] != nullptr) {
                sf::Vector2f size = (sf::Vector2f) this->items[y][x]->sprite.getTexture()->getSize();
                float largestSize = size.x > size.y ? size.x : size.y;
                this->items[y][x]->sprite.setOrigin(size * 0.5f);
                this->items[y][x]->sprite.setScale((1.0f / largestSize) * sf::Vector2f(0.7f, 0.7f) * scale);
                if (!selected || selectedPos.x != x || selectedPos.y != y)
                    this->items[y][x]->sprite.setPosition((0.0f - dimensions.x * 0.5f + 0.5f + x) * scale,
                                                          (0.0f - dimensions.y * 0.5f + 0.5f + y) * scale);
                this->items[y][x]->draw();
            }
        }
    }

    GameManager::window.setView(oldView);
}


