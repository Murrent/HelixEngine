//
// Created by Martin on 2021-01-27.
//

#include "vmath.h"
#include <cmath>

float vmath::Length(sf::Vector2f vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

float vmath::Length(float x, float y) {
    return sqrtf(x * x + y * y);
}

float vmath::SqrLength(sf::Vector2f vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

float vmath::SqrLength(float x, float y) {
    return x * x + y * y;
}

sf::Vector2f vmath::Normalized(sf::Vector2f vec) {
    return vec * (1 / Length(vec));
}

sf::Vector2f vmath::Normalized(float x, float y) {
    return sf::Vector2f(x, y) * (1 / Length(sf::Vector2f(x, y)));
}

float vmath::Dot(sf::Vector2f vecA, sf::Vector2f vecB) {
    return vecA.x * vecB.x + vecA.y * vecB.y;
}

float vmath::Cross(sf::Vector2f vecA, sf::Vector2f vecB) {
    return vecA.x * vecB.y - vecA.y * vecB.x;
}

sf::Vector2f vmath::CrossF(float s, sf::Vector2f vecA) {
    return sf::Vector2f(-s * vecA.y, s * vecA.x);
}

sf::Vector2f vmath::CrossF(sf::Vector2f vecA, float s) {
    return sf::Vector2f(s * vecA.y, -s * vecA.x);
}
