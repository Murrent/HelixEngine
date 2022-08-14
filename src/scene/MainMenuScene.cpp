#include <SFML/Window/Event.hpp>
#include <iostream>
#include "MainMenuScene.hpp"
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

void MainMenuScene::init() {
    //MainMenuScene mainMenuScene;
    //Scene *abc = &mainMenuScene;

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
//    int level[256];
//    for (int &i : level) {
//        i = 3;
//    }
//    int levelNthn[256];
//    for (int &i : levelNthn) {
//        i = 0;
//    }
//    rngRefreshSeed();
//    // create the tilemap from the level definition
//    if (!GameManager::map.setTileset("../assets/sprites/Tiles.png"))
//        return;

    if (!MapGenerator::setup(GameManager::map, "../assets/sprites/Tiles.png", rngRefreshSeed(), "World1"))
        return;

//    int noiseLevel[256];
//    sf::Vector2i offset(0,-1);
//    sf::Vector2f scale(0.1f,0.1f);
//    sf::Vector2f seedOffset(0,0);
//    for (int i = 0; i < 16; i++) {
//        for (int j = 0; j < 16; j++) {
//            noiseLevel[i + j * 16] = int((SimplexNoise::noise((float)(i * offset.x + seedOffset.x) * scale.x, (float)(j * offset.y + seedOffset.y) * scale.y) + 1.0f) * 0.5f * 4.0f);
//        }
//    }
//
//    if (!GameManager::map.addChunk(sf::Vector2u(4, 4), noiseLevel, 0, -1))
//        return;
//
//    offset.x = 0;
//    offset.y = 0;
//    for (int i = 0; i < 16; i++) {
//        for (int j = 0; j < 16; j++) {
//            noiseLevel[i + j * 16] = int((SimplexNoise::noise((float)(i * offset.x + seedOffset.x) * scale.x, (float)(j * offset.y + seedOffset.y) * scale.y) + 1.0f) * 0.5f * 4.0f);
//        }
//    }
//
//    if (!GameManager::map.addChunk(sf::Vector2u(4, 4), noiseLevel, 0, 0))
//        return;
//
//    offset.x = 0;
//    offset.y = 1;
//    for (int i = 0; i < 16; i++) {
//        for (int j = 0; j < 16; j++) {
//            noiseLevel[i + j * 16] = int((SimplexNoise::noise((float)(i * offset.x + seedOffset.x) * scale.x, (float)(j * offset.y + seedOffset.y) * scale.y) + 1.0f) * 0.5f * 4.0f);
//        }
//    }
//
//    if (!GameManager::map.addChunk(sf::Vector2u(4, 4), noiseLevel, 0, 1))
//        return;
//
//    offset.x = -1;
//    offset.y = 0;
//    for (int i = 0; i < 16; i++) {
//        for (int j = 0; j < 16; j++) {
//            noiseLevel[i + j * 16] = int((SimplexNoise::noise((float)(i * offset.x + seedOffset.x) * scale.x, (float)(j * offset.y + seedOffset.y) * scale.y) + 1.0f) * 0.5f * 4.0f);
//        }
//    }
//
//    if (!GameManager::map.addChunk(sf::Vector2u(4, 4), noiseLevel, -1, 0))
//        return;
//
//    offset.x = -1;
//    offset.y = -1;
//    for (int i = 0; i < 16; i++) {
//        for (int j = 0; j < 16; j++) {
//            noiseLevel[i + j * 16] = int((SimplexNoise::noise((float)(i * offset.x + seedOffset.x) * scale.x, (float)(j * offset.y + seedOffset.y) * scale.y) + 1.0f) * 0.5f * 4.0f);
//        }
//    }
//
//    if (!GameManager::map.addChunk(sf::Vector2u(4, 4), noiseLevel, -1, -1))
//        return;
//
//    offset.x = 1;
//    offset.y = -1;
//    for (int i = 0; i < 16; i++) {
//        for (int j = 0; j < 16; j++) {
//            noiseLevel[i + j * 16] = int((SimplexNoise::noise((float)(i * offset.x + seedOffset.x) * scale.x, (float)(j * offset.y + seedOffset.y) * scale.y) + 1.0f) * 0.5f * 4.0f);
//        }
//    }
//
//    if (!GameManager::map.addChunk(sf::Vector2u(4, 4), noiseLevel, 1, -1))
//        return;
//
//    offset.x = 0;
//    offset.y = -2;
//    for (int i = 0; i < 16; i++) {
//        for (int j = 0; j < 16; j++) {
//            noiseLevel[i + j * 16] = int((SimplexNoise::noise((float)(i * offset.x + seedOffset.x) * scale.x, (float)(j * offset.y + seedOffset.y) * scale.y) + 1.0f) * 0.5f * 4.0f);
//        }
//    }
//
//    if (!GameManager::map.addChunk(sf::Vector2u(4, 4), noiseLevel, 0, -2))
//        return;
//    GameManager::map.setTile(10, -1, 3);
//
//
//    GameManager::map.setTile(0, -1, "Stone");
//    GameManager::map.setTile(0, -2, "Iron ore");
//    GameManager::map.setTile(0, -3, "Gold ore");
//    GameManager::map.setTile(0, -4, "Dirt");
//    GameManager::map.setTile(0, -5, "Grass");
//
//    GameManager::map.setTile(4, 0, 0);
//    GameManager::map.setTile(5, 0, 0);
//    GameManager::map.setTile(6, 0, 0);
//    GameManager::map.setTile(4, 1, 0);
//    GameManager::map.setTile(5, 1, 0);
//    GameManager::map.setTile(4, 2, 0);
//    GameManager::map.setTile(5, 2, 0);
//    GameManager::map.setTile(4, 3, 0);
//    GameManager::map.setTile(5, 3, 0);
//    GameManager::map.setTile(6, 3, 0);
//    GameManager::map.setTile(4, 4, 0);
//    GameManager::map.setTile(5, 4, 0);
//    GameManager::map.setTile(6, 4, 0);
//    GameManager::map.setTile(4, 5, 0);
//    GameManager::map.setTile(5, 5, 0);
//    GameManager::map.setTile(6, 5, 0);
//    GameManager::map.setTile(4, 6, 0);
//    GameManager::map.setTile(5, 6, 0);
//    GameManager::map.setTile(6, 6, 0);
//    GameManager::map.setTile(1, 1, 1);
//    GameManager::map.setTile(0, 3, 1);
//    GameManager::map.setTile(15, 0, 2);
//    //map.removeChunk(sf::Vector2i(-3, 0));

    this->view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(64, 32));
    GameManager::window.setView(this->view);
    GameManager::player = Player(2.0f, -10.0f, 0.8f, 1.8f);
    GameManager::player.setVelocity(sf::Vector2f(0.0f, 0.0f));
    GameManager::player.shape.setFillColor(sf::Color(255, 255, 255, 100));
    GameManager::physicsManager.players.push_back(&GameManager::player);


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
    sf::Vector2f plPos = GameManager::player.shape.getPosition();
    //plPos = sf::Vector2f (std::floor(plPos.x), std::floor(plPos.y));
    //sf::Vector2f correction = sf::Vector2f(float(int(tmp.getSize().x) % 2 == 0 ? 0 : 1) * 0.5f,
    //                                       float(int(tmp.getSize().y) % 2 == 0 ? 0 : 1) * 0.5f);

    //tmp.setCenter(floor(plPos.x) + correction.x, floor(plPos.y) + correction.y);
    tmp.setCenter(plPos);
    //tmp.setSize(std::floor(tmp.getSize().x), std::floor(tmp.getSize().y));
    GameManager::window.setView(tmp);
//    if (Input::input.getEvent(NEXT).getActive()) {
//        sf::View tmp = GameManager::window.getView();
//        tmp.setCenter(tmp.getCenter().x, tmp.getCenter().y + 1.f);
//        GameManager::window.setView(tmp);
//    }
//    if (Input::input.getEvent(PREVIOUS).getActive()) {
//        sf::View tmp = GameManager::window.getView();
//        tmp.setCenter(tmp.getCenter().x, tmp.getCenter().y - 1.f);
//        GameManager::window.setView(tmp);
//    }
//    if (Input::input.getEvent(TRIGGER).getUp()) {
//        sf::View tmp = GameManager::window.getView();
//        tmp.setCenter(tmp.getCenter().x + 1.f, tmp.getCenter().y);
//        GameManager::window.setView(tmp);
//    }
//    if (Input::input.getEvent(TRIGGER2).getUp()) {
//        sf::View tmp = GameManager::window.getView();
//        tmp.setCenter(tmp.getCenter().x - 1.f, tmp.getCenter().y);
//        GameManager::window.setView(tmp);
//    }

//    sf::Vector2f vel = player.getVelocity();
//    if (Input::input.getEvent(LEFT).getActive())
//        vel.x -= 0.04f;
//    if (Input::input.getEvent(RIGHT).getActive())
//        vel.x += 0.04f;
//
//    if (Input::input.getEvent(JUMP).getDown())
//        vel.y -= 0.6f;
//    else
//        vel.y += 0.02f;
//
//    vel.x *= 0.8f;
//    vel.y *= 0.99f;
//
//    player.setVelocity(vel);
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

void MainMenuScene::draw() {
    GameManager::window.clear();
    GameManager::window.draw(GameManager::map);
    GameManager::physicsManager.draw();
    GameManager::player.draw();
    text.setPosition(GameManager::player.getPosition() - sf::Vector2f(2.0f, 10.0f));
    GameManager::window.draw(text);
    GameManager::window.display();
}

void MainMenuScene::end() {
    GameManager::player.inventory.clear();
    Scene::end();
}
