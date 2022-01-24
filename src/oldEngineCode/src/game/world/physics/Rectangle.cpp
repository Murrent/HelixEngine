//
// Created by Martin on 2021-01-02.
//

#include "Rectangle.h"
#include "physics.h"
Rectangle::Rectangle(float density, float width, float height) {
    rectangleShape = sf::RectangleShape();
    rectangleShape.setSize(sf::Vector2f(300,100));
    rectangleShape.setFillColor(sf::Color::White);
    position = velocity = gravity = force =  sf::Vector2f(0,0);
    rotation = angularVelocity = torque = friction = 0;
    width = width;
    height = height;
    mass = density * width * height;
    inertia = (width * height * height * height)/12.0f;
    /*sf::Vector2f A, B, C;
    A = sf::Vector2f(-width/2, height/2);
    B = sf::Vector2f(width/2, height/2);
    C = sf::Vector2f(width/2, -height/2);
    float mass_triA = density * 0.5f * std::abs(Physics::Cross(A, B));
    float mass_triB = density * 0.5f * std::abs(Physics::Cross(B, C));
    printf("%f a %f b\n", A.x, A.y);
    printf("%f a %f b\n", B.x, B.y);
    printf("%f a %f b\n",C.x, C.y);
    inertia += mass_triA * (Physics::SqrLength(A) + Physics::SqrLength(B) + Physics::Dot(A, B))/6;
    inertia += mass_triA * (Physics::SqrLength(A) + Physics::SqrLength(B) + Physics::Dot(A, B))/6;
    inertia += mass_triB * (Physics::SqrLength(B) + Physics::SqrLength(C) + Physics::Dot(B, C))/6;
    inertia += mass_triB * (Physics::SqrLength(B) + Physics::SqrLength(C) + Physics::Dot(B, C))/6;*/
    printf("%f inertia %f mass\n", inertia, mass);
}

void Rectangle::Draw(sf::RenderWindow &window) {
    rectangleShape.setSize(sf::Vector2f(300,100));
    rectangleShape.setFillColor(sf::Color::Blue);
    rectangleShape.setOrigin(150, 50);
    rectangleShape.setPosition(position);
    rectangleShape.setRotation(rotation);
    //printf("%f - %f\n", rectangleShape.getPosition().x, rectangleShape.getPosition().y);
    window.draw(rectangleShape);
}
