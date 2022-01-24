//
// Created by Martin on 2020-12-29.
//

#include "MainMenu.h"

MainMenu::MainMenu() {
    play = Button();
    options = Button();
    exit = Button();
    style = ButtonStyle();

    play.GetSprite()->setPosition(100,100);
    options.GetSprite()->setPosition(100,200);
    exit.GetSprite()->setPosition(100,300);

    play.SetButtonHoverStyle(style);
    options.SetButtonHoverStyle(style);
    exit.SetButtonHoverStyle(style);

    play.SetButtonPressStyle(style);
    options.SetButtonPressStyle(style);
    exit.SetButtonPressStyle(style);

    play.SetButtonNormalStyle(style);
    options.SetButtonNormalStyle(style);
    exit.SetButtonNormalStyle(style);
}
