
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "game/world/Chunk.h"
#include "game/world/ChunkHandler.h"
#include "noise.h"
#include <cmath>
int main()
{
    sf::VideoMode desktop = sf::VideoMode(1080, 1080);
    sf::RenderWindow window(desktop, "Game");
    window.clear(sf::Color::Black);
    window.display();
    window.setFramerateLimit(60);
    sf::View view(sf::Vector2f(0,0), sf::Vector2f(1080, 1080));
    auto* chunkHandler = new ChunkHandler();
    sf::Texture texture;
    if (!texture.loadFromFile("texture.png"))
        return -1;
    //chunkHandler->AddChunk(sf::Vector2i(-1,-1), texture);
    //chunkHandler->AddChunk(sf::Vector2i(0,0), texture);
    //chunkHandler->AddChunk(sf::Vector2i(1,-1), texture);

    sf::Texture texture2;
    if(!texture2.create(200,200))
        return 0;
    sf::Sprite sprite(texture2);
    sprite.setScale(5,5);
    sprite.setPosition(0,0);

    printf("start");
    noise::SetSeed(1);
    sf::Uint8 pixels[4*200*200];
    printf("%f\n", noise::GetSeedValue(0) * 2.0f - 1.0f);
    printf("%f\n", noise::GetSeedValue(1) * 2.0f - 1.0f);
    printf("%f\n", noise::GetSeedValue(1) * 2.0f - 1.0f);
    printf("%f\n", noise::GetSeedValue(1 + 1) * 2.0f - 1.0f);
    printf("%f\n", noise::GetSeedValue(2) * 2.0f - 1.0f);
    printf("%f\n", noise::GetSeedValue(2 + 1) * 2.0f - 1.0f);
    printf("%f\n", noise::GetSeedValue(3) * 2.0f - 1.0f);
    printf("%f\n", noise::GetSeedValue(3 + 1) * 2.0f - 1.0f);
    for (int i = 0; i < 8*sizeof(pixels)/sizeof(sf::Uint8*); i+=4) {
        pixels[i] = 255;
        pixels[i+1] = 255;
        pixels[i+2] = 255;
        pixels[i+3] = 255 * noise::get2D(std::fmod(float(i)/16.0f, 200.0f) / 4.0f, std::floor(float(i)/4.f/200.f) / 16.0f);
        //printf("%f\n", std::floor(float(i)/4.f/50.f) / Chunk::size);
    }
    printf("updating");
    texture2.update(pixels);
    printf("done");

    sf::Clock fpsClock;
    float frameTime = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //if (fpsClock.getElapsedTime().asSeconds() - frameTime > 0.01/* && sf::Mouse::isButtonPressed(sf::Mouse::Right)*/){
            //printf("%f\n", fpsClock.getElapsedTime().asSeconds() - frameTime);
            window.setView(view);
            view.setCenter((sf::Vector2f)sf::Mouse::getPosition(window));
            window.clear(sf::Color::Black);

            chunkHandler->Draw(window);
            window.draw(sprite);

            window.display();
            frameTime = fpsClock.getElapsedTime().asSeconds();
        //}
    }
    return 0;
}