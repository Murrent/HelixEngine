#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class Scene {
public:
    Scene();
    virtual void init();
    virtual void update();
    virtual void draw();
    virtual void end();

};

