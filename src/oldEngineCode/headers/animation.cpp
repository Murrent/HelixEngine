//
// Created by Martin on 2020-12-28.
//
#include "animation.h"
sf::Vector2f Animation::LerpV2(sf::Vector2f start, sf::Vector2f end, float speed) {
    return sf::Vector2f(std::lerp(start.x, end.x, speed), std::lerp(start.y, end.y, speed));
}
float Animation::LerpF(float start, float end, float speed) {
    return std::lerp(start, end, speed);
}
sf::Color Animation::LerpCol(sf::Color start, sf::Color end, float speed) {
    return sf::Color(std::lerp(start.r, end.r, speed),
                     std::lerp(start.g, end.g, speed),
                     std::lerp(start.b, end.b, speed),
                     std::lerp(start.a, end.a, speed));
}