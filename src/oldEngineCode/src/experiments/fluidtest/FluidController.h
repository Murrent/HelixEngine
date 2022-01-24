//
// Created by Martin on 2021-01-12.
//

#ifndef GAMEENGINE_FLUIDCONTROLLER_H
#define GAMEENGINE_FLUIDCONTROLLER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class FluidController {
private:
    sf::RenderWindow *window{};
    sf::Image image;
    sf::Image prevImage;
    sf::Texture texture;
    sf::Sprite sprite;
    void Initialize();
    void Draw();
    bool UpdatePixels();
    sf::Vector2i UpdateWaterPixel(int x, int y);
    sf::Vector2i FindSpot(int x, int y);
    bool TrySpot(int x, int y);
    static bool IsInBounds(int value, int start, int end);
public:
    void Run();

    virtual ~FluidController();

};


#endif //GAMEENGINE_FLUIDCONTROLLER_H
