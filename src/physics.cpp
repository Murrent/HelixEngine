#include <cstdio>
#include "oldEngineCode/oldPhysicsManager/PhysicsManager.hpp"
#include "physics/PhysicsObject.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
int main() {
    PhysicsManager manager;
    manager.Init();

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(60);
    RoundLine line;
    line.start = Vector2f(300.f, 500.f);
    line.end = Vector2f(700.f, 200.f);
    RoundLine line2;
    line2.start = Vector2f(100.f, 200.f);
    line2.end = Vector2f(400.f, 500.f);

    manager.staticLines.emplace_back(line);
    manager.staticLines.emplace_back(line2);

    Circle circle;
    circle.pos = Vector2f (400.f, 100.f);
    circle.shape.setRadius(Circle::radius);
    circle.shape.setOrigin(Circle::radius, Circle::radius);
    manager.circles.emplace_back(circle);


    Circle circle2;
    circle2.pos = Vector2f (200.f, 100.f);
    circle2.shape.setRadius(Circle::radius);
    circle2.shape.setOrigin(Circle::radius, Circle::radius);
    manager.circles.emplace_back(circle2);


    Circle circle3;
    circle3.pos = Vector2f (300.f, 100.f);
    circle3.shape.setRadius(Circle::radius);
    circle3.shape.setOrigin(Circle::radius, Circle::radius);
    manager.circles.emplace_back(circle3);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //manager.staticLines[0].end = (sf::Vector2f)sf::Mouse::getPosition(window);
        manager.Update();
        window.clear(sf::Color(150, 150, 150));
        manager.Draw(window);
        window.display();
    }
    return EXIT_SUCCESS;
}