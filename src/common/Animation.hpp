#pragma once


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

sf::Vector2f LerpV2(sf::Vector2f start, sf::Vector2f end, float speed);

float LerpF(float start, float end, float speed);

sf::Color LerpCol(sf::Color start, sf::Color end, float speed);


