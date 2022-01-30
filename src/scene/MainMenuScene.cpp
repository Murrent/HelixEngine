#include <SFML/Window/Event.hpp>
#include <iostream>
#include "MainMenuScene.hpp"
#include "GameManager.hpp"
#include "../system/Input.hpp"

void MainMenuScene::init() {
    MainMenuScene mainMenuScene;
    Scene* abc = &mainMenuScene;

    // create the window
    //sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap");

    // define the level with an array of tile indices
//    const int level[] =
//            {
//                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//                    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
//                    1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
//                    0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
//                    0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
//                    0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
//                    2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
//                    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//            };
    int level[256];
    for (int &i : level) {
        i = 3;
    }
    // create the tilemap from the level definition
    if (!map.setTileset("../assets/sprites/Tiles.png"))
        return;
    if (!map.addChunk(sf::Vector2u(4, 4), level, 0, 0))
        return;
    if (!map.addChunk(sf::Vector2u(4, 4), level, 0, 1))
        return;
    if (!map.addChunk(sf::Vector2u(4, 4), level, -1, 0))
        return;
    if (!map.addChunk(sf::Vector2u(4, 4), level, -1, -1))
        return;
    if (!map.addChunk(sf::Vector2u(4, 4), level, 1, -1))
        return;
    if (!map.addChunk(sf::Vector2u(4, 4), level, 0, -2))
        return;
    map.setTile(4, 0, 0);
    map.setTile(5, 0, 0);
    map.setTile(6, 0, 0);
    map.setTile(4, 1, 0);
    map.setTile(5, 1, 0);
    map.setTile(4, 2, 0);
    map.setTile(5, 2, 0);
    map.setTile(4, 3, 0);
    map.setTile(5, 3, 0);
    map.setTile(6, 3, 0);
    map.setTile(4, 4, 0);
    map.setTile(5, 4, 0);
    map.setTile(6, 4, 0);
    map.setTile(4, 5, 0);
    map.setTile(5, 5, 0);
    map.setTile(6, 5, 0);
    map.setTile(4, 6, 0);
    map.setTile(5, 6, 0);
    map.setTile(6, 6, 0);
    map.setTile(1, 1, 1);
    map.setTile(0, 4, 1);
    map.setTile(15, 0, 2);
    //map.removeChunk(sf::Vector2i(-3, 0));

    this->view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(80, 40));
    GameManager::window.setView(this->view);
    player = Player(2.0f, -10.0f, 0.8f, 1.8f);
    player.setVelocity(sf::Vector2f(0.0f, 0.0f));
    player.shape.setFillColor(sf::Color(255, 255, 255, 100));
    physicsManager.rectangles.push_back(&player);
}

void MainMenuScene::update() {
    Input::input.scrollReset();
    sf::Event event{};
    while (GameManager::window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            GameManager::window.close();
        else if (event.type == sf::Event::MouseMoved) {
            //sf::View tmp = GameManager::window.getView();

//            tmp.setCenter(GameManager::window.mapPixelToCoords(sf::Mouse::getPosition(GameManager::window)) -
//                          GameManager::window.getView().getCenter());
            //std::cout << tmp.getCenter().x << " " << tmp.getCenter().y << std::endl;
            //GameManager::window.setView(tmp);
        } else if (event.type == sf::Event::Resized) {
            sf::View tmp = GameManager::window.getView();
            tmp.setSize(64.f * static_cast<float>(GameManager::window.getSize().x) / 2000.f,
                        32.f * static_cast<float>(GameManager::window.getSize().y) / 1000.f);
            GameManager::window.setView(tmp);
        } else if (event.type == sf::Event::MouseWheelScrolled) {
            Input::input.scrollUpdate(event);
        }
    }


    Input::input.update();

    //std::cout << (Input::input.getEvent(UP).getActive()) << std::endl;


    if (Input::input.getEvent(NEXT).getActive()) {
        sf::View tmp = GameManager::window.getView();
        tmp.setCenter(tmp.getCenter().x, tmp.getCenter().y + 1.f);
        GameManager::window.setView(tmp);
    }
    if (Input::input.getEvent(PREVIOUS).getActive()) {
        sf::View tmp = GameManager::window.getView();
        tmp.setCenter(tmp.getCenter().x, tmp.getCenter().y - 1.f);
        GameManager::window.setView(tmp);
    }
    if (Input::input.getEvent(TRIGGER).getUp()) {
        sf::View tmp = GameManager::window.getView();
        tmp.setCenter(tmp.getCenter().x + 1.f, tmp.getCenter().y);
        GameManager::window.setView(tmp);
    }
    if (Input::input.getEvent(TRIGGER2).getUp()) {
        sf::View tmp = GameManager::window.getView();
        tmp.setCenter(tmp.getCenter().x - 1.f, tmp.getCenter().y);
        GameManager::window.setView(tmp);
    }

    sf::Vector2f vel = player.getVelocity();
    if (Input::input.getEvent(LEFT).getActive())
        vel.x -= 0.04f;
    if (Input::input.getEvent(RIGHT).getActive())
        vel.x += 0.04f;

    if (Input::input.getEvent(JUMP).getDown())
        vel.y -= 0.6f;
    else
        vel.y += 0.02f;

    vel.x *= 0.8f;
    vel.y *= 0.99f;

    player.setVelocity(vel);
    physicsManager.update(map);
}

void MainMenuScene::draw() {
    GameManager::window.clear();
    GameManager::window.draw(map);
    GameManager::window.draw(player.shape);
    GameManager::window.display();
}

void MainMenuScene::end() {
    Scene::end();
}
