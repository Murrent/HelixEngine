#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Textures.hpp"

class GameManager {
private:
    static void init();
    static void update();
    static void draw();
    static void end();
public:
    static Scene* scene;
    static sf::RenderWindow window;
    static Textures textures;
    static void stop();
    static void run();
};

