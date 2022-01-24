//
// Created by Martin on 2021-01-12.
//

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdlib>
#include <ctime>
#include "FluidController.h"

void FluidController::Run() {
    Initialize();
    sf::Clock fpsClock;
    float frameTime = 0;
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        if (fpsClock.getElapsedTime().asSeconds() - frameTime > 0.01 && sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            //printf("Update\n");
            UpdatePixels();
            texture.update(image);
            Draw();
            frameTime = fpsClock.getElapsedTime().asSeconds();
        }
    }
}

void FluidController::Initialize() {
    srand (time(nullptr));
    sf::VideoMode desktop = sf::VideoMode(1080, 1080);
    window = new sf::RenderWindow(desktop, "Game", sf::Style::Default);
    window->clear(sf::Color::Black);
    window->display();
    window->setFramerateLimit(60);

    if (!texture.create(100, 100))
        return;
    image.create(100,100, sf::Color::Black);
    texture.update(image);
    sprite.setTexture(texture);
    sprite.setScale(10,10);
    sprite.setPosition(0,0);

    printf("start");
    for (int x = 40; x < 60; x+= 1) {
        for (int y = 10; y < 90; y++) {
            image.setPixel(x, y, sf::Color::Blue);
        }
    }
    printf("updating");
    texture.update(image);
    printf("done");
}

void FluidController::Draw() {
    window->clear(sf::Color::Black);

    window->draw(sprite);

    window->display();
}

FluidController::~FluidController() {
    free(window);
}

bool FluidController::UpdatePixels() {
    bool found = false;
    prevImage = image;
    sf::Color color;
    sf::Vector2i newPos = sf::Vector2i(-1, -1);
    for (int x = 0; x < (int)image.getSize().x; ++x) {
        for (int y = 0; y < (int)image.getSize().y ; y++) {
            color = prevImage.getPixel(x, y);
            newPos = sf::Vector2i(-1, -1);
            if (color == sf::Color::Blue) { newPos = UpdateWaterPixel(x, y); }

            if ((newPos.x != -1 && newPos.y != -1) && (newPos.x != x || newPos.y != y)){
                image.setPixel(newPos.x, newPos.y, color);
                image.setPixel(x, y, sf::Color::Black);
            }
        }
    }
    return false;
}

bool FluidController::IsInBounds(int value, int start, int end) {
    if (value <= end && value >= start)
        return true;
    else
        return false;
}

sf::Vector2i FluidController::UpdateWaterPixel(int x, int y) {
    FindSpot(x, y);
    return FindSpot(x, y);
}

sf::Vector2i FluidController::FindSpot(int x, int y) {
    sf::Vector2i spot = sf::Vector2i(x, y);
    int direction = rand() % 2 + 1;
    bool below, left, right, dl, dr;
    below = TrySpot(x, y + 1);
    left = TrySpot(x - 1, y);
    right = TrySpot(x + 1, y);
    dl = TrySpot(x - 1, y + 1);
    dr = TrySpot(x + 1, y + 1);
    if (below) spot = sf::Vector2i(x, y + 1);
    else if (dl && !dr) spot = sf::Vector2i(x - 1, y + 1);
    else if (dr && !dl) spot = sf::Vector2i(x + 1, y + 1);
    else if (direction == 1 && dl) spot = sf::Vector2i(x - 1, y + 1);
    else if (direction == 2 && dr) spot = sf::Vector2i(x + 1, y + 1);
    else if (left && !right) spot = sf::Vector2i(x - 1, y);
    else if (right && !left) spot = sf::Vector2i(x + 1, y);
    else if (direction == 1 && right) spot = sf::Vector2i(x + 1, y);
    else if (direction == 2 && left) spot = sf::Vector2i(x - 1, y);
    return spot;
}

bool FluidController::TrySpot(int x, int y) {
    if (IsInBounds(x, 0, (int)image.getSize().x - 1) &&
        IsInBounds(y, 0, (int)image.getSize().y - 1)) {
        if (image.getPixel(x, y) == sf::Color::Black && prevImage.getPixel(x, y) == sf::Color::Black) return true;
    }
    return false;
}
