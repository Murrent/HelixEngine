//
// Created by Martin on 2021-01-02.
//

#ifndef GAMEENGINE_PHYSICS_H
#define GAMEENGINE_PHYSICS_H
#include <SFML/System/Vector2.hpp>
struct Matrix2
{
    float m00, m01,
          m10, m11;

    Matrix2();
    Matrix2(float _m00, float _m01, float _m10, float _m11);
    //Create from angle in radians
    void Set(float radians);

    [[nodiscard]] Matrix2 Transpose() const;

    sf::Vector2f operator*(sf::Vector2f rhs) const;

    Matrix2 operator*(Matrix2 rhs) const;
};
namespace Physics {
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

    sf::Vector2f LocalToWorld(sf::Vector2f vec, float rotation, sf::Vector2f local);
    sf::Vector2f WorldToLocal(sf::Vector2f vec, float rotation, sf::Vector2f local);

    bool PointInTriangle(sf::Vector2f point, sf::Vector2f corner1, sf::Vector2f corner2, sf::Vector2f corner3);
    bool LineLine(sf::Vector2f startA, sf::Vector2f endA, sf::Vector2f startB, sf::Vector2f endB, sf::Vector2f* point, sf::Vector2f* distance);
};



#endif //GAMEENGINE_PHYSICS_H
