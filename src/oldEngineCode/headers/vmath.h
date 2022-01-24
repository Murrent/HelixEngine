//
// Created by Martin on 2021-01-27.
//

#ifndef GAMEENGINE_VMATH_H
#define GAMEENGINE_VMATH_H
#include <SFML/System/Vector2.hpp>

namespace vmath {
    float Length(sf::Vector2f vec);
    float Length(float x, float y);

    float SqrLength(sf::Vector2f vec);
    float SqrLength(float x, float y);

    sf::Vector2f Normalized(sf::Vector2f vec);
    sf::Vector2f Normalized(float x, float y);

    float Dot(sf::Vector2f vecA, sf::Vector2f vecB);

    float Cross(sf::Vector2f vecA, sf::Vector2f vecB);
    sf::Vector2f CrossF(float s, sf::Vector2f vecA);
    sf::Vector2f CrossF(sf::Vector2f vecA, float s);
};


#endif //GAMEENGINE_VMATH_H
