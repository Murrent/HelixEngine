//
// Created by Martin on 2020-12-28.
//

#include "ButtonStyle.h"

ButtonStyle::ButtonStyle() {
    color = sf::Color(100, 0, 50, 255);
    size = sf::Vector2f (50.0f, 20.0f);
}
ButtonStyle::ButtonStyle(sf::Vector2f _size) {
    size = _size;
    color = sf::Color(100, 0, 50, 255);
}
ButtonStyle::ButtonStyle(sf::Color _color) {
    size = sf::Vector2f (50.0f, 20.0f);
    color = _color;
}
ButtonStyle::ButtonStyle(sf::Vector2f _size, sf::Color _color) {
    size = _size;
    color = _color;
}
sf::Vector2f ButtonStyle::GetSize() {
    return size;
}
sf::Color ButtonStyle::GetColor() {
    return color;
}
void ButtonStyle::SetSize(sf::Vector2f _size) {
    size = _size;
}
void ButtonStyle::SetColor(sf::Color _color) {
    color = _color;
}
