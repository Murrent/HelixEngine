//
// Created by Martin on 2021-01-12.
//
#include <SFML/Graphics.hpp>
#include <physics.h>
#include "PhysicsTest_.h"
#include "PhysicsHandler.h"
#include "Rectangle.h"
#include "../../../ui/Button.h"

void PhysicsTest_::PressTest() {
    printf("Pressed\n");
}
void PhysicsTest_::Run() {
    PhysicsHandler physicsHandler;
    Rectangle rectangle(1.f, 100.0f, 50.0f);
    physicsHandler.shapes.push_back(&rectangle);
    rectangle.position.y = 300;
    rectangle.AddTorque(100000);
    rectangle.AddForce(sf::Vector2f(900, 0));
    rectangle.position.x = 300;

    sf::Texture texture;
    if(!texture.create(200,200))
        return;
    sf::Sprite sprite(texture);
    sprite.setScale(5,5);
    sprite.setPosition(10,10);

    printf("start");
    sf::Uint8 pixels[4*200*200];
    for (int i = 0; i < 8*sizeof(pixels)/sizeof(sf::Uint8*); ++i) {
        pixels[i] = (unsigned char)(i % 255);
    }
    printf("updating");
    texture.update(pixels);
    printf("done");

    Button button = Button();
    //button.SetPressAction(this->PressTest);
    button.GetSprite()->setPosition(500, 300);
    button.SetButtonHoverStyle(ButtonStyle(sf::Vector2f(340.0f, 180.0f)));
    button.SetButtonPressStyle(ButtonStyle(sf::Vector2f(310.0f, 160.0f)));
    button.SetButtonNormalStyle(ButtonStyle(sf::Vector2f(300.0f, 150.0f)));
    // create the window
    sf::VideoMode desktop = sf::VideoMode(1920, 1080);
    sf::RenderWindow window(desktop, "Game", sf::Style::Default);
    window.setFramerateLimit(60);
    sf::View mouseCam;
    mouseCam.reset(sf::FloatRect(0, 0, 1920, 1080));
    mouseCam.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.f));
    window.setView(mouseCam);
    //for (int i = 0; i < sf::VideoMode::getDesktopMode(); ++i) {
    //    printf("%d %d\n", sf::VideoMode::getDesktopMode()[i].width, sf::VideoMode::getDesktopMode()[i].height);
    //}
    // run the program as long as the window is open
    //------------------------------------------------------------------
    //---------------------TRIANGLE TESTING-----------------------------

    sf::VertexArray triangle(sf::LinesStrip, 4);
    triangle[0].position = sf::Vector2f(100, 100);
    triangle[0].color  = sf::Color::Green;
    triangle[1].position = sf::Vector2f(400, 200);
    triangle[1].color = sf::Color::Green;
    triangle[2].position = sf::Vector2f(200, 250);
    triangle[2].color = sf::Color::Green;
    triangle[3].position = sf::Vector2f(100, 100);
    triangle[3].color = sf::Color::Green;

    sf::VertexArray mouse(sf::Lines, 6);
    mouse[0].position = sf::Vector2f(100, 100);
    mouse[0].color  = sf::Color::Red;
    mouse[1].position = sf::Vector2f(600, 500);
    mouse[1].color = sf::Color::Red;
    mouse[2].position = sf::Vector2f(400, 200);
    mouse[2].color = sf::Color::Red;
    mouse[3].position = sf::Vector2f(600, 500);
    mouse[3].color = sf::Color::Red;
    mouse[4].position = sf::Vector2f(200, 250);
    mouse[4].color  = sf::Color::Red;
    mouse[5].position = sf::Vector2f(600, 500);
    mouse[5].color = sf::Color::Red;
    //------------------------------------------------------------------
    bool pressing = false;
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        rectangle.rectangleShape.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            rectangle.AddForceAtPosition(rectangle.position, ((sf::Vector2f)sf::Mouse::getPosition(window) - rectangle.position));
            pressing = true;
        }
        //mouseCam.move((sf::Vector2f)sf::Mouse::getPosition(window)/100.f);
        //window.setView(mouseCam);
        physicsHandler.Update(1);
        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        //button.Update(&window);

        //window.draw(*button.GetSprite());

        //window.draw(sprite);
        rectangle.Draw(window);
        //------------------------------------------------------------------
        //---------------------TRIANGLE TESTING-----------------------------
        mouse[1].position = (sf::Vector2f)sf::Mouse::getPosition(window);
        mouse[3].position = (sf::Vector2f)sf::Mouse::getPosition(window);
        mouse[5].position = (sf::Vector2f)sf::Mouse::getPosition(window);
        if (Physics::PointInTriangle(mouse[1].position, triangle[0].position, triangle[1].position , triangle[2].position)){
            triangle[0].color = sf::Color::Green;
            triangle[1].color = sf::Color::Green;
            triangle[2].color = sf::Color::Green;
            triangle[3].color = sf::Color::Green;
        } else {
            triangle[0].color = sf::Color::Blue;
            triangle[1].color = sf::Color::Blue;
            triangle[2].color = sf::Color::Blue;
            triangle[3].color = sf::Color::Blue;
        }

        window.draw(triangle);
        window.draw(mouse);

        //------------------------------------------------------------------
        //window.draw(rectangle.rectangleShape);
        // end the current frame
        window.display();
    }

}

