#include "Animation.hpp"

float LerpF(float start, float end, float speed) {
    return start + speed * (end - start);
}

sf::Vector2f LerpV2(sf::Vector2f start, sf::Vector2f end, float speed) {
    return sf::Vector2f(LerpF(start.x, end.x, speed), LerpF(start.y, end.y, speed));
}

sf::Color LerpCol(sf::Color start, sf::Color end, float speed) {
    return sf::Color(LerpF(start.r, end.r, speed),
                     LerpF(start.g, end.g, speed),
                     LerpF(start.b, end.b, speed),
                     LerpF(start.a, end.a, speed));
}