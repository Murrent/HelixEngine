#pragma once

#include "Scene.hpp"
#include "../tilemap/TileMap.hpp"
#include "../physics/PhysicsManager.hpp"
#include "../content/Player.hpp"

class MainMenuScene : public Scene {
public:
    sf::View view;
    void init() override;
    void update() override;
    void draw() override;
    void end() override;
};


