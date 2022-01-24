//
// Created by Martin on 2021-01-02.
//

#include "physics.h"

#include <cmath>

Matrix2::Matrix2() {
    m00 = 0.f;
    m01 = 0.f;
    m10 = 0.f;
    m11 = 0.f;
}
Matrix2::Matrix2(float _m00, float _m01, float _m10, float _m11) {
    m00 = _m00;
    m01 = _m01;
    m10 = _m10;
    m11 = _m11;
}
//Create from angle in radians
void Matrix2::Set(float radians) {
    float c = std::cos(radians);
    float s = std::sin(radians);

    m00 = c; m01 = -s;
    m10 = s; m11 =  c;
}

Matrix2 Matrix2::Transpose() const {
    return Matrix2(m00, m10,
                   m01, m11);
}

sf::Vector2f Matrix2::operator*(sf::Vector2f rhs) const {
    return sf::Vector2f(m00 * rhs.x + m01 * rhs.y, m10 * rhs.x + m11 * rhs.y);
}

Matrix2 Matrix2::operator*(Matrix2 rhs ) const {
    return Matrix2(
            m00 * rhs.m00 + m01 * rhs.m10, m00 * rhs.m01 + m01 * rhs.m11,
            m10 * rhs.m00 + m11 * rhs.m10, m10 * rhs.m01 + m11 * rhs.m11);
}

float Physics::Length(sf::Vector2f vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

float Physics::Length(float x, float y) {
    return sqrtf(x * x + y * y);
}

float Physics::SqrLength(sf::Vector2f vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

float Physics::SqrLength(float x, float y) {
    return x * x + y * y;
}

sf::Vector2f Physics::Normalized(sf::Vector2f vec) {
    return vec * (1 / Length(vec));
}

sf::Vector2f Physics::Normalized(float x, float y) {
    return sf::Vector2f(x, y) * (1 / Length(sf::Vector2f(x, y)));
}

float Physics::Dot(sf::Vector2f vecA, sf::Vector2f vecB) {
    return vecA.x * vecB.x + vecA.y * vecB.y;
}

float Physics::Cross(sf::Vector2f vecA, sf::Vector2f vecB) {
    return vecA.x * vecB.y - vecA.y * vecB.x;
}

sf::Vector2f Physics::CrossF(float s, sf::Vector2f vecA) {
    return sf::Vector2f(-s * vecA.y, s * vecA.x);
}

sf::Vector2f Physics::CrossF(sf::Vector2f vecA, float s) {
    return sf::Vector2f(s * vecA.y, -s * vecA.x);
}

sf::Vector2f Physics::LocalToWorld(sf::Vector2f vec, float rotation, sf::Vector2f local) {
    Matrix2 u;
    u.Set(rotation);
    return local + u * vec;
}

sf::Vector2f Physics::WorldToLocal(sf::Vector2f vec, float rotation, sf::Vector2f local) {
    Matrix2 u;
    u.Set(rotation);
    return u.Transpose() * (vec - local);
}

bool Physics::PointInTriangle(sf::Vector2f point, sf::Vector2f corner1, sf::Vector2f corner2, sf::Vector2f corner3) {
    float w1 =  (corner1.x * (corner3.y - corner1.y) + (point.y - corner1.y) * (corner3.x - corner1.x) - point.x * (corner3.y - corner1.y))/
                ((corner2.y - corner1.y) * (corner3.x - corner1.x) - (corner2.x - corner1.x) * (corner3.y - corner1.y));
    float w2 =  (point.y - corner1.y - w1 * (corner2.y - corner1.y))/
                (corner3.y - corner1.y);
    if (w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1)
        return true;
    else
        return false;
}
//Distance will be from startA to intersection point
bool
Physics::LineLine(sf::Vector2f startA, sf::Vector2f endA, sf::Vector2f startB, sf::Vector2f endB, sf::Vector2f *point,
                  sf::Vector2f *distance) {
    float h = (endB.y-startB.y)*(endA.x-startA.x) - (endB.x-startB.x)*(endA.y-startA.y);
    float uA = ((endB.x-startB.x)*(startA.y-startB.y) - (endB.y-startB.y)*(startA.x-startB.x)) / h;
    float uB = ((endA.x-startA.x)*(startA.y-startB.y) - (endA.y-startA.y)*(startA.x-startB.x)) / h;

    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
        float intersectionX = startA.x + (uA * (endA.x-startA.x));
        float intersectionY = startA.y + (uA * (endA.y-startA.y));
        *point = sf::Vector2f(intersectionX, intersectionY);
        *distance = (*point) - startA;
        return true;
    }
    return false;
}
