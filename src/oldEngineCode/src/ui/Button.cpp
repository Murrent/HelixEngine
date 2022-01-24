//
// Created by Martin on 2020-12-27.
//

#include <SFML/Graphics/Texture.hpp>
#include "Button.h"
Button::Button() {
    sprite = sf::Sprite();
    sf::Texture texture;
    texture.create(1, 1);
    sprite.setTexture(texture);
    action = nullptr;
    hover = ButtonStyle();
    press = ButtonStyle();
    normal = ButtonStyle();
    lastState = false;
}
Button::Button(void (*_action)()) {
    sprite = sf::Sprite();
    sf::Texture texture;
    texture.create(1, 1);
    sprite.setTexture(texture);
    action = _action;
    hover = ButtonStyle();
    press = ButtonStyle();
    normal = ButtonStyle();
    lastState = false;
}
void Button::SetPressAction(void (*_action)()) {action = _action;}
sf::Sprite * Button::GetSprite() {return &sprite;}
void Button::OnHover() {
    sprite.setScale(
            Animation::LerpV2(
                    sprite.getScale(),
                    hover.GetSize(), 0.5f));
    sprite.setColor(Animation::LerpCol(sprite.getColor(), hover.GetColor(), 0.5f));
}
void Button::OnPress() {
    sprite.setScale(
            Animation::LerpV2(
                    sprite.getScale(),
                    press.GetSize(), 0.5f));
    sprite.setColor(Animation::LerpCol(sprite.getColor(), press.GetColor(), 0.5f));
}
void Button::OnRelease() {
    (*action)();
}
void Button::Update(sf::RenderWindow* window) {
    sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(*window);
    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f size = sf::Vector2f (sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    //printf("x %f", sprite.getOrigin().x);
    //printf("y %f", sprite.getOrigin().y);
    bool pressing = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    if (pos.x + size.x/2 > mouse.x &&
        pos.x - size.x/2 < mouse.x &&
        pos.y + size.y/2 > mouse.y &&
        pos.y - size.y/2 < mouse.y){
        if (pressing){
            OnPress();
        }
        else if (lastState)
            OnRelease();
        else
            OnHover();
    } else {
        sprite.setScale(
                Animation::LerpV2(
                        sprite.getScale(),
                        normal.GetSize(), 0.5f));
        sprite.setOrigin(Animation::LerpF(sprite.getOrigin().x, sprite.getLocalBounds().width/2, 0.5f),
                         Animation::LerpF(sprite.getOrigin().y, sprite.getLocalBounds().height/2, 0.5f));
        sprite.setColor(Animation::LerpCol(sprite.getColor(), normal.GetColor(), 0.5f));
    }
    lastState = pressing;
}

const ButtonStyle *Button::GetButtonHoverStyle() {return &hover;}
const ButtonStyle *Button::GetButtonPressStyle() {return &press;}
const ButtonStyle *Button::GetButtonNormalStyle() {return &normal;}
void Button::SetButtonHoverStyle(ButtonStyle style) {hover = style;}
void Button::SetButtonPressStyle(ButtonStyle style) {press = style;}
void Button::SetButtonNormalStyle(ButtonStyle style) {normal = style;}
