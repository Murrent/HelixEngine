//
// Created by Martin on 2021-01-27.
//

#include "noise.h"
#include <cmath>
#include "vmath.h"
#include <SFML/System/Vector2.hpp>
#include <cstdio>
#include <random>

float Fade(float t) {
    return 6 * powf(t, 5) - 15 * powf(t, 4) + 10 * powf(t, 3);
}

float noise::GetSeedValue(int _seed) {
    std::default_random_engine r(_seed);
    return float(r() % 1000000) / 1000000.f;
}

void noise::SetSeed(int _seed) { seed = _seed; }

float noise::get1D(int x) {
    return 0;
}

float noise::get2D(float x, float y) {
    sf::Vector2i chunk(floorf(x), floorf(y));
    sf::Vector2f tile(x, y);
    sf::Vector2f v1 = (sf::Vector2f) chunk + sf::Vector2f(0.0f, 0.0f) - (sf::Vector2f) tile;
    sf::Vector2f v2 = (sf::Vector2f) chunk + sf::Vector2f(1.0f, 0.0f) - (sf::Vector2f) tile;
    sf::Vector2f v3 = (sf::Vector2f) chunk + sf::Vector2f(0.0f, 1.0f) - (sf::Vector2f) tile;
    sf::Vector2f v4 = (sf::Vector2f) chunk + sf::Vector2f(1.0f, 1.0f) - (sf::Vector2f) tile;
    //printf("%d - %d \n", tile.x, tile.y);
    sf::Vector2f cv1(GetSeedValue(chunk.x + chunk.y) * 2.0f - 1.0f, GetSeedValue(chunk.x + chunk.y) * 2.0f - 1.0f);
    sf::Vector2f cv2(GetSeedValue(chunk.x + chunk.y + 1) * 2.0f - 1.0f, GetSeedValue(chunk.x + chunk.y) * 2.0f - 1.0f);
    sf::Vector2f cv3(GetSeedValue(chunk.x + chunk.y) * 2.0f - 1.0f, GetSeedValue(chunk.x + chunk.y + 1) * 2.0f - 1.0f);
    sf::Vector2f cv4(GetSeedValue(chunk.x + chunk.y + 1) * 2.0f - 1.0f,
                     GetSeedValue(chunk.x + chunk.y + 1) * 2.0f - 1.0f);
    //printf("%f - %f\n%f - %f\n%f - %f\n%f - %f\n\n", v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, v4.x, v4.y);
    float dotA = vmath::Dot(v1, cv1);
    float dotB = vmath::Dot(v2, cv2);
    float dotC = vmath::Dot(v3, cv3);
    float dotD = vmath::Dot(v4, cv4);
    //printf("%f - %f - %f - %f\n", dotA, dotB, dotC, dotD);
    float ab = dotA + tile.x * (dotB - dotA);
    float cd = dotC + tile.x * (dotD - dotC);
    float value = ab + tile.y * (cd - ab);
    //value = Fade(value);
    //printf("%f\n", value);
    return value;
}

