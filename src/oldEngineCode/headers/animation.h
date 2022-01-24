//
// Created by Martin on 2020-12-28.
//

#ifndef GAMEENGINE_ANIMATION_H
#define GAMEENGINE_ANIMATION_H
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
namespace Animation {
    sf::Vector2f LerpV2(sf::Vector2f start, sf::Vector2f end, float speed);
    float LerpF(float start, float end, float speed);
    sf::Color LerpCol(sf::Color start, sf::Color end, float speed);
}

#endif //GAMEENGINE_ANIMATION_H
