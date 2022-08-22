#include <SFML/Window/Event.hpp>
#include <iostream>
#include "GameScene.hpp"
#include "GameManager.hpp"
#include "../system/Input.hpp"
#include "../content/items/Stick.hpp"
#include "../content/items/SwordIron.hpp"
#include "../content/items/IngotGold.hpp"
#include "../content/items/IngotIron.hpp"
#include "../content/items/PickaxeIron.hpp"
#include "../content/items/Banana.hpp"
#include "../tilemap/MapGenerator.hpp"
#include "../content/items/TileItem.hpp"
#include "../common/Random.hpp"
#include "../common/Animation.hpp"

void GameScene::init() {
    if (!MapGenerator::setup(GameManager::map, "../assets/sprites/Tiles.png", rngRefreshSeed(), "World1"))
        return;

    this->view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(64, 32));
    GameManager::window.setView(this->view);
    GameManager::player = Player(2.0f, -10.0f, 0.8f, 1.8f);
    GameManager::player.setVelocity(sf::Vector2f(0.0f, 0.0f));
    GameManager::player.shape.setFillColor(sf::Color(255, 255, 255, 100));
    GameManager::physicsManager.players.push_back(&GameManager::player);
    GameManager::clock.update();

    {
        auto *stick = new SwordIron();
        if (!GameManager::player.inventory.addItem(stick))
            delete stick;
    }
    {
        auto *stick = new PickaxeIron();
        if (!GameManager::player.inventory.addItem(stick))
            delete stick;
    }
    {
        auto *stick = new IngotGold();
        if (!GameManager::player.inventory.addItem(stick))
            delete stick;
    }
    {
        auto *stick = new IngotIron();
        if (!GameManager::player.inventory.addItem(stick))
            delete stick;
    }
    {
        auto *stick = new Banana();
        if (!GameManager::player.inventory.addItem(stick))
            delete stick;
    }
    {
        auto *stick = new TileItem(GameManager::map.tileLookupTable[1]);
        stick->amount = 64;
        if (!GameManager::player.inventory.addItem(stick))
            delete stick;
    }


    this->text.setString("hello");
    this->text.setScale(0.02f, 0.02f);
    this->text.setCharacterSize(24);
    this->text.setFillColor(sf::Color::Red);
    this->text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    this->text.setFont(GameManager::resources.fonts["tahoma"]);
}

void GameScene::update() {
    GameManager::clock.update();
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
            sf::Vector2f diff = sf::Vector2f(GameManager::window.getSize().x, GameManager::window.getSize().y) /
                                (float) GameManager::window.getSize().y;
            tmp.setSize(64.f * diff.x,
                        64.f * diff.y);
            GameManager::window.setView(tmp);
        } else if (event.type == sf::Event::MouseWheelScrolled) {
            Input::input.scrollUpdate(event);
        }
    }


    Input::input.update();

    //std::cout << (Input::input.getEvent(UP).getActive()) << std::endl;

    sf::View tmp = GameManager::window.getView();
    sf::Vector2f plPos = LerpV2(tmp.getCenter(), GameManager::player.shape.getPosition(), 10.0f * GameManager::clock.delta());
    //plPos = sf::Vector2f (std::floor(plPos.x), std::floor(plPos.y));
    //sf::Vector2f correction = sf::Vector2f(float(int(tmp.getSize().x) % 2 == 0 ? 0 : 1) * 0.5f,
    //                                       float(int(tmp.getSize().y) % 2 == 0 ? 0 : 1) * 0.5f);

    //tmp.setCenter(floor(plPos.x) + correction.x, floor(plPos.y) + correction.y);
    tmp.setCenter(plPos);
    //tmp.setSize(std::floor(tmp.getSize().x), std::floor(tmp.getSize().y));
    GameManager::window.setView(tmp);
    auto chunkPos = sf::Vector2f(GameManager::player.getPosition() / (float) Chunk::size);
    auto chunkPosi = sf::Vector2i(std::floor(chunkPos.x), std::floor(chunkPos.y));

    for (int i = chunkPosi.x - 1; i < chunkPosi.x + 2; ++i) {
        for (int j = chunkPosi.y - 3; j < chunkPosi.y + 3; ++j) {
            if (!GameManager::map.chunkExists(i, j))
                MapGenerator::generateChunk(GameManager::map, i, j);
        }
    }

    GameManager::player.updateInputs();
    GameManager::physicsManager.update();

    sf::Vector2i mousePos = sf::Mouse::getPosition(GameManager::window);
    sf::Vector2f worldPos = GameManager::window.mapPixelToCoords(mousePos);
    std::string posString = "x:" + std::to_string(worldPos.x) + " y:" + std::to_string(worldPos.y) + " Tile: " +
                            GameManager::map.tileLookupTable[GameManager::map.getTileType(worldPos.x,
                                                                                          worldPos.y)].name +
                            "/n" + "x:" + std::to_string(chunkPosi.x) + " y:" + std::to_string(chunkPosi.y);
    this->text.setString(posString);
}

void GameScene::draw() {
    GameManager::window.clear();
    GameManager::window.draw(GameManager::map);
    GameManager::physicsManager.draw();
    GameManager::player.draw();
    text.setPosition(GameManager::player.getPosition() - sf::Vector2f(2.0f, 10.0f));
    GameManager::window.draw(text);
    GameManager::window.display();
}

void GameScene::end() {
    GameManager::player.inventory.clear();
    Scene::end();
}
