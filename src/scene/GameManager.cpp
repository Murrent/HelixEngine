
#include <iostream>
#include "GameManager.hpp"
#include "GameScene.hpp"

Scene* GameManager::scene = nullptr;
sf::RenderWindow GameManager::window;
TileMap GameManager::map;
PhysicsManager GameManager::physicsManager;
Player GameManager::player;
Resources GameManager::resources;

void GameManager::init() {
    GameManager::window.create(sf::VideoMode(1000, 500), "SFML works!");
    //GameManager::window.setFramerateLimit(60);
    GameManager::resources.load("../assets/");
    GameManager::scene = new GameScene();

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


