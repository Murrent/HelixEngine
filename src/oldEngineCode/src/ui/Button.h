//
// Created by Martin on 2020-12-27.
//

#ifndef GAMEENGINE_BUTTON_H
#define GAMEENGINE_BUTTON_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include "ButtonStyle.h"
#include "animation.h"

class Button {
private:
    void (*action)();
    sf::Sprite sprite;
    ButtonStyle hover, press, normal;
    bool lastState;
public:
    Button();
    explicit Button(void (*_action)());
    const ButtonStyle* GetButtonHoverStyle();
    const ButtonStyle* GetButtonPressStyle();
    const ButtonStyle* GetButtonNormalStyle();
    void SetButtonHoverStyle(ButtonStyle style);
    void SetButtonPressStyle(ButtonStyle style);
    void SetButtonNormalStyle(ButtonStyle style);
    void SetPressAction(void (*_action)());
    sf::Sprite* GetSprite();
    virtual void OnHover();
    virtual void OnPress();
    virtual void OnRelease();
    virtual void Update(sf::RenderWindow* window);
};


#endif //GAMEENGINE_BUTTON_H
