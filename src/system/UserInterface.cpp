#include <iostream>
#include "UserInterface.hpp"
#include "../scene/GameManager.hpp"
#include "../common/Animation.hpp"

// ANIMATIONS

void std_animation_hovered(UI::Panel &panel) {
    panel.style.color = sf::Color::Green;
}

void std_animation_pressed(UI::Panel &panel) {
    panel.style.color = sf::Color::Red;
}

void std_animation_released(UI::Panel &panel) {
    panel.style.color = sf::Color::White;
}

// PANEL

UI::Panel::Panel() = default;

void UI::Panel::hovered() {
    switch (animation) {
        default:
            std_animation_hovered(*this);
            break;
    }
}

void UI::Panel::pressed() {
    switch (animation) {
        default:
            std_animation_pressed(*this);
            break;
    }
}

void UI::Panel::released() {
    switch (animation) {
        default:
            std_animation_released(*this);
            break;
    }
}

void UI::Panel::start() {
    Entity::start();
    sprite.setTexture(GameManager::resources.textures["banana"]);
    sprite.setPosition(style.position);
    sprite.setScale(style.size);
    sprite.setColor(style.color);
}

void UI::Panel::update() {
    Entity::update();
    sprite.setColor(LerpCol(sprite.getColor(), style.color, 0.1f * GameManager::clock.delta()));
}

void UI::Panel::draw() {
    Entity::draw();
    std::cout << "drawing ui panel" << std::endl;
    GameManager::window.draw(sprite);
}

// BUTTON

UI::Button::Button() = default;

void UI::Button::start() {
    Panel::start();
    text.setString("Default text");
}

void UI::Button::update() {
    Panel::update();
}

void UI::Button::draw() {
    Panel::draw();
    GameManager::window.draw(text);
}

// CANVAS

UI::Canvas::Canvas() = default;

void UI::Canvas::start() {
    Entity::start();
    for (auto &panel : panels) {
        panel.start();
    }
    for (auto &button : buttons) {
        button.start();
    }
}

void UI::Canvas::update() {
    Entity::update();
    for (auto &panel : panels) {
        panel.update();
    }
    for (auto &button : buttons) {
        button.update();
    }
}

void UI::Canvas::draw() {
    Entity::draw();
    sf::View view = GameManager::window.getView();

    sf::View tmpView(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
    tmpView.setViewport(area);
    tmpView.setSize(area.width * (float) GameManager::window.getSize().x,
                    area.height * (float) GameManager::window.getSize().y);
    tmpView.setCenter(tmpView.getSize() * 0.5f);
    GameManager::window.setView(tmpView);

    for (auto &panel : panels) {
        panel.draw();
    }
    for (auto &button : buttons) {
        button.draw();
    }

    GameManager::window.setView(view);
}

// USER INTERFACE

UI::UserInterface::UserInterface() = default;

void UI::UserInterface::start() {
    Entity::start();
    for (auto &canvas : canvases) {
        canvas.start();
    }
}

void UI::UserInterface::update() {
    Entity::update();
    for (auto &canvas : canvases) {
        canvas.update();
    }
}

void UI::UserInterface::draw() {
    Entity::draw();
    for (auto &canvas : canvases) {
        canvas.draw();
    }
}

