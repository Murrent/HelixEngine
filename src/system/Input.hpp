#pragma once

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

enum InputIndex {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    JUMP,
    TRIGGER,
    TRIGGER2,
    TRIGGER3,
    INTERACT,
    NEXT,
    PREVIOUS,
    SPRINT,
    INVENTORY,
    DROPITEM,
    HOTBAR1,
    HOTBAR2,
    HOTBAR3,
    HOTBAR4,
    HOTBAR5,
    HOTBAR6,
    HOTBAR7,
    HOTBAR8,
    HOTBAR9,
    HOTBAR10,
    INPUT_COUNT
};

class InputEvent {
    friend class Input;

protected:
    bool down{false}, up{false}, active{false};

    unsigned int storedIndex{0};

    InputIndex inputIndex{};

    virtual void pressedBehavior();

    virtual void releasedBehavior();

    virtual void update() {};

public:
    bool getDown() const;

    bool getUp() const;

    bool getActive() const;
};

class KeyEvent : public InputEvent {
    friend class Input;

private:
    sf::Keyboard::Key key;

    void update() override;

public:
    explicit KeyEvent(sf::Keyboard::Key keyValue);
};

class MouseBtnEvent : public InputEvent {
    friend class Input;

private:
    sf::Mouse::Button button;

    void update() override;

public:
    explicit MouseBtnEvent(sf::Mouse::Button mouseBtn);
};

class ScrollEvent : public InputEvent {
    friend class Input;

private:
    sf::Mouse::Wheel wheel;
    bool positive;

    void scrollUpdate(sf::Event &event);

public:
    ScrollEvent(sf::Mouse::Wheel wheelType, bool positiveDirection);
};

class Input {
private:
    std::vector<KeyEvent> keyInputs;
    std::vector<MouseBtnEvent> mouseInputs;
    std::vector<ScrollEvent> scrollInputs;

    std::vector<InputEvent *> inputs;
public:
    static Input input;

    Input();

    InputEvent &getEvent(InputIndex index);

    bool remap(InputIndex index, sf::Keyboard::Key key);

    bool remap(InputIndex index, sf::Mouse::Button button);

    bool remap(InputIndex index, sf::Mouse::Wheel wheel, bool positiveDirection);

    void update();

    void scrollUpdate(sf::Event &event);

    void scrollReset();
};

