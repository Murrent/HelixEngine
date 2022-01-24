//
// Created by Martin on 2020-12-28.
//

#ifndef GAMEENGINE_BUTTONSTYLE_H
#define GAMEENGINE_BUTTONSTYLE_H
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

class ButtonStyle {
private:
    sf::Vector2f size;
    sf::Color color;
public:
    ButtonStyle();
    explicit ButtonStyle(sf::Vector2f _size);
    explicit ButtonStyle(sf::Color _color);
    ButtonStyle(sf::Vector2f _size, sf::Color _color);
    sf::Vector2f GetSize();
    sf::Color GetColor();
    void SetColor(sf::Color _color);
    void SetSize(sf::Vector2f _size);
};


#endif //GAMEENGINE_BUTTONSTYLE_H
