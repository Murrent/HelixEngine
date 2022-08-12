#include <SFML/Graphics/View.hpp>
#include <iostream>
#include "Hotbar.hpp"
#include "../scene/GameManager.hpp"
#include "../system/Input.hpp"

Hotbar::Hotbar() : size(0), selected(0) {}

Hotbar::Hotbar(unsigned int slots, unsigned int selectedSlot) : size(slots), selected(selectedSlot) {}

void Hotbar::update() {
    Entity::update();
    if (Input::input.getEvent(NEXT).getActive()) {
        selected++;
        selected = std::clamp(selected, (unsigned int) 0, (unsigned int) items.size() - 1);
    } else if (Input::input.getEvent(PREVIOUS).getActive() && selected != 0) {
        selected--;
        selected = std::clamp(selected, (unsigned int) 0, (unsigned int) items.size() - 1);
    } else if (Input::input.getEvent(HOTBAR1).getDown())
        selected = 0;
    else if (Input::input.getEvent(HOTBAR2).getDown())
        selected = 1;
    else if (Input::input.getEvent(HOTBAR3).getDown())
        selected = 2;
    else if (Input::input.getEvent(HOTBAR4).getDown())
        selected = 3;
    else if (Input::input.getEvent(HOTBAR5).getDown())
        selected = 4;
    else if (Input::input.getEvent(HOTBAR6).getDown())
        selected = 5;
    else if (Input::input.getEvent(HOTBAR7).getDown())
        selected = 6;
    else if (Input::input.getEvent(HOTBAR8).getDown())
        selected = 7;
    else if (Input::input.getEvent(HOTBAR9).getDown())
        selected = 8;
    else if (Input::input.getEvent(HOTBAR10).getDown())
        selected = 9;

}

void Hotbar::draw() {
    Entity::draw();
    this->background.setSize(sf::Vector2f((float) items.size(), 1));
    this->background.setOrigin(sf::Vector2f((float) items.size(), 1) * 0.5f);
    sf::View oldView = GameManager::window.getView();
    sf::Vector2u windowSize = GameManager::window.getSize();
    sf::View tmpView(sf::Vector2f(0, 0), (sf::Vector2f) windowSize);
    float scale = tmpView.getSize().y * 0.08f;
    this->background.setPosition(0.0f, (0.05f - 0.50f * scale) + (float) windowSize.y * 0.5f);
    this->background.setScale(scale, scale);
    GameManager::window.setView(tmpView);
    GameManager::window.draw(this->background);

    for (int y = 0; y < this->items.size(); y++) {
        sf::RectangleShape rect;
        rect.setOrigin(this->background.getSize() * scale * 0.5f);
        rect.setFillColor(sf::Color(80, 80, 80));
        if (y == selected) {
            rect.setFillColor(sf::Color(150, 150, 150));
        }
        rect.setSize(sf::Vector2f(0.9f, 0.9f) * scale);
        rect.setPosition((0.05f + (float) y) * scale, (0.05f - 0.45f * scale) + (float) windowSize.y * 0.5f);
        GameManager::window.draw(rect);
    }

    sf::Text text;
    text.setFont(GameManager::resources.fonts["tahoma"]);
    text.setFillColor(sf::Color::Black);
    for (int y = 0; y < this->items.size(); y++) {
        if (this->items[y] != nullptr) {
            sf::Vector2f textureSize = sf::Vector2f(this->items[y]->sprite.getTextureRect().width,
                                                    this->items[y]->sprite.getTextureRect().height);

            float largestSize = textureSize.x > textureSize.y ? textureSize.x : textureSize.y;
            this->items[y]->sprite.setOrigin(textureSize * 0.5f);
            this->items[y]->sprite.setScale((1.0f / largestSize) * sf::Vector2f(0.7f, 0.7f) * scale);
            //if (!selected || selected != y)
                this->items[y]->sprite.setPosition((0.0f - (float) this->items.size() * 0.5f + 0.5f + y) * scale,
                                                   ((0.05f - 0.50f * scale) + (float) windowSize.y * 0.5f));
            this->items[y]->draw();

            text.setString(std::to_string(this->items[y]->amount) + "/" + std::to_string(this->items[y]->stackSize));
            text.setPosition((0.0f - (float) this->items.size() * 0.5f + 0.5f + y) * scale,
                             ((0.05f - 0.50f * scale) + (float) windowSize.y * 0.5f));
            text.setScale(sf::Vector2f(0.01f, 0.01f) * scale);
            GameManager::window.draw(text);
        }
    }

    GameManager::window.setView(oldView);
}

void Hotbar::start() {
    Entity::start();
    this->background.setPosition(0.0f, 0.0f);
    this->background.setFillColor(sf::Color(100, 100, 100));
}

Item *Hotbar::getSelectedItem() {
    return items[selected];
}

void Hotbar::dropEquippedItem(sf::Vector2f velocity) {
    Inventory &inventory = GameManager::player.inventory;
    inventory.dropItem(sf::Vector2u(selected, inventory.getDimensions().y - 1), velocity);
    items[selected] = nullptr;
}


