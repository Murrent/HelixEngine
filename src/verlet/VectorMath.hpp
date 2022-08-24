#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

using namespace sf;

Vector2f Normal(Vector2f a, Vector2f b);

float Dist(Vector2f a, Vector2f b);

float SqrDist(Vector2f a, Vector2f b);

bool PointCircle(Vector2f &p, Vector2f &c, float r);

bool LinePoint(Vector2f &a, Vector2f &b, Vector2f &p);

Vector2f LineLine(Vector2f a, Vector2f b, Vector2f c, Vector2f d);
