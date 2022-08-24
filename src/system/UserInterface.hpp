#pragma once

#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Entity.hpp"

namespace UI {

    enum AnimationType {
        STD_ANIM
    };

    enum Anchor {
        MIDDLE,
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    };

    struct PanelStyle {
        sf::Color color = sf::Color::White;;
        sf::Vector2f size{10.0f, 10.0f};
        sf::Vector2f position{0.0f, 0.0f};
        float rotation = 0;
    };

    class Panel : public Entity {
    public:
        sf::Sprite sprite;
        PanelStyle style;
        Anchor anchor = MIDDLE;
        AnimationType animation = STD_ANIM;

        Panel();

        virtual void hovered();

        virtual void pressed();

        virtual void released();

        void start() override;

        void update() override;

        void draw() override;
    };

    class Button : public Panel {
    public:
        bool disabled = false;

        void (*action)() = nullptr;

        sf::Text text;

        Button();

        void start() override;

        void update() override;

        void draw() override;
    };

    class TextBox : public Panel {

    };

    class Slider : public Panel {

    };

    class ScrollBar : public Panel {

    };

    class Canvas : public Entity {
    public:
        sf::FloatRect area = sf::FloatRect(0.0f, 0.0f, 0.5f, 1.0f);
        std::vector<Panel> panels;
        std::vector<Button> buttons;

        Canvas();

        void start() override;

        void update() override;

        void draw() override;
    };

    class UserInterface : public Entity {
    public:
        std::vector<Canvas> canvases;

        UserInterface();

        void start() override;

        void update() override;

        void draw() override;
    };
}