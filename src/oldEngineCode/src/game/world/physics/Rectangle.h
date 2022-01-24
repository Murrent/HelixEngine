//
// Created by Martin on 2021-01-02.
//

#ifndef GAMEENGINE_RECTANGLE_H
#define GAMEENGINE_RECTANGLE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Shape.h"

class Rectangle : public Shape {
public:
    sf::RectangleShape rectangleShape;
    Rectangle(float density, float width, float height);
    void Draw(sf::RenderWindow& window);
};


#endif //GAMEENGINE_RECTANGLE_H
