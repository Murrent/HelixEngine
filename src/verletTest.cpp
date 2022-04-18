#include <SFML/Graphics.hpp>
#include <iostream>
#include "physics/Solver.hpp"
#include <cstdlib>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML window");
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(800, 800));
    window.setView(view);
    window.setFramerateLimit(60);

    Solver solver;
    std::vector<VerletObject> objects;
    std::vector<sf::Color> colors;

    sf::CircleShape shape;

    srand(time(NULL));

    sf::Clock clock;
    sf::Clock eventClock;
    float delta = 0;
    while (delta < 1) {
        delta = clock.getElapsedTime().asSeconds();
        window.clear(sf::Color(150, 150, 150));

        shape.setFillColor(sf::Color::Cyan);
        shape.setRadius(300);
        shape.setOrigin(300, 300);
        shape.setPosition(sf::Vector2f(0, 0));
        window.draw(shape);

        for (auto &obj : objects) {
            shape.setFillColor(sf::Color::Red);
            shape.setRadius(obj.size);
            shape.setOrigin(obj.size, obj.size);
            shape.setPosition(obj.position);
            window.draw(shape);
        }


        window.display();
    }

    clock.restart();
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && eventClock.getElapsedTime().asSeconds() > 0.05f) {
            objects.emplace_back();
            colors.emplace_back();
            objects[objects.size() - 1].position.x = 200;
            objects[objects.size() - 1].prevPosition.x = 200;
            objects[objects.size() - 1].accelerate(sf::Vector2f(-20000, -70000));
            objects[objects.size() - 1].size = rand() % 10 + 5;
            colors[objects.size() - 1] = sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);

            eventClock.restart();
        }

        delta = clock.getElapsedTime().asSeconds();
        //std::cout << delta << std::endl;
        solver.update(objects, delta);
        clock.restart();

        window.clear(sf::Color(150, 150, 150));


        shape.setFillColor(sf::Color::Cyan);
        shape.setRadius(300);
        shape.setOrigin(300, 300);
        shape.setPosition(sf::Vector2f(0, 0));
        window.draw(shape);


        for (int i = 0; i < objects.size(); i++) {
            shape.setFillColor(sf::Color::Red);
            shape.setRadius(objects[i].size);
            shape.setOrigin(objects[i].size, objects[i].size);
            shape.setPosition(objects[i].position);
            shape.setFillColor(colors[i]);
            window.draw(shape);
        }

        window.display();
    }
    return EXIT_SUCCESS;
}