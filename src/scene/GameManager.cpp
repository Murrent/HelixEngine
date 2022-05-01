
#include <iostream>
#include "GameManager.hpp"
#include "MainMenuScene.hpp"

Scene* GameManager::scene = nullptr;
sf::RenderWindow GameManager::window;
TileMap GameManager::map;
PhysicsManager GameManager::physicsManager;
Player GameManager::player;
Textures GameManager::textures;

void GameManager::init() {
    GameManager::window.create(sf::VideoMode(1000, 500), "SFML works!");
    GameManager::window.setFramerateLimit(60);
    GameManager::textures.load("../assets/sprites/items/");
    GameManager::scene = new MainMenuScene();

    GameManager::scene->init();
}

void GameManager::update() {
    GameManager::scene->update();
}

void GameManager::draw() {
    GameManager::scene->draw();
}

void GameManager::end() {
    GameManager::scene->end();
}

void GameManager::run() {
    GameManager::init();
    while (GameManager::window.isOpen()) {
        GameManager::update();
        GameManager::draw();
    }
    GameManager::end();
    GameManager::stop();
    delete (GameManager::scene);
}

void GameManager::stop() {
    GameManager::window.close();
}


