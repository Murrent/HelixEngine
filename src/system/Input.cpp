#include "Input.hpp"

bool InputEvent::getDown() const {
    return this->down;
}

bool InputEvent::getUp() const {
    return this->up;
}

bool InputEvent::getActive() const {
    return this->active;
}

void InputEvent::pressedBehavior() {
    if (!this->active)
        this->down = true;
    else
        this->down = false;
    this->active = true;
    this->up = false;
}

void InputEvent::releasedBehavior() {
    if (this->active)
        this->up = true;
    else
        this->up = false;
    this->active = false;
    this->down = false;
}

void KeyEvent::update() {
    if (sf::Keyboard::isKeyPressed(this->key)) {
        this->pressedBehavior();
    } else {
        this->releasedBehavior();
    }
}

KeyEvent::KeyEvent(sf::Keyboard::Key keyValue) {
    this->key = keyValue;
}

void MouseBtnEvent::update() {
    if (sf::Mouse::isButtonPressed(this->button))
        this->pressedBehavior();
    else
        this->releasedBehavior();
}

MouseBtnEvent::MouseBtnEvent(sf::Mouse::Button mouseBtn) {
    this->button = mouseBtn;
}

void ScrollEvent::scrollUpdate(sf::Event &event) {
    if (event.mouseWheelScroll.wheel == this->wheel) {
        if ((this->positive && event.mouseWheelScroll.delta > 0.0f) ||
            (!this->positive && event.mouseWheelScroll.delta < 0.0f))
            this->pressedBehavior();
        else
            this->releasedBehavior();
    }
}

ScrollEvent::ScrollEvent(sf::Mouse::Wheel wheelType, bool positiveDirection) {
    this->wheel = wheelType;
    this->positive = positiveDirection;
}

Input::Input() {
    inputs.resize(INPUT_COUNT);
//    UP
    keyInputs.emplace_back(KeyEvent(sf::Keyboard::W));
    keyInputs.back().storedIndex = keyInputs.size() - 1;
    keyInputs.back().inputIndex = UP;
//    DOWN
    keyInputs.emplace_back(KeyEvent(sf::Keyboard::S));
    keyInputs.back().storedIndex = keyInputs.size() - 1;
    keyInputs.back().inputIndex = DOWN;
//    LEFT
    keyInputs.emplace_back(KeyEvent(sf::Keyboard::A));
    keyInputs.back().storedIndex = keyInputs.size() - 1;
    keyInputs.back().inputIndex = LEFT;
//    RIGHT
    keyInputs.emplace_back(KeyEvent(sf::Keyboard::D));
    keyInputs.back().storedIndex = keyInputs.size() - 1;
    keyInputs.back().inputIndex = RIGHT;
//    JUMP
    keyInputs.emplace_back(KeyEvent(sf::Keyboard::Space));
    keyInputs.back().storedIndex = keyInputs.size() - 1;
    keyInputs.back().inputIndex = JUMP;
//    TRIGGER
    mouseInputs.emplace_back(MouseBtnEvent(sf::Mouse::Left));
    mouseInputs.back().storedIndex = mouseInputs.size() - 1;
    mouseInputs.back().inputIndex = TRIGGER;
//    TRIGGER2
    mouseInputs.emplace_back(MouseBtnEvent(sf::Mouse::Right));
    mouseInputs.back().storedIndex = mouseInputs.size() - 1;
    mouseInputs.back().inputIndex = TRIGGER2;
//    TRIGGER3
    mouseInputs.emplace_back(MouseBtnEvent(sf::Mouse::Middle));
    mouseInputs.back().storedIndex = mouseInputs.size() - 1;
    mouseInputs.back().inputIndex = TRIGGER3;
//    INTERACT
    keyInputs.emplace_back(KeyEvent(sf::Keyboard::E));
    keyInputs.back().storedIndex = keyInputs.size() - 1;
    keyInputs.back().inputIndex = INTERACT;
//    NEXT
    scrollInputs.emplace_back(ScrollEvent(sf::Mouse::VerticalWheel, true));
    scrollInputs.back().storedIndex = scrollInputs.size() - 1;
    scrollInputs.back().inputIndex = NEXT;
//    PREVIOUS
    scrollInputs.emplace_back(ScrollEvent(sf::Mouse::VerticalWheel, false));
    scrollInputs.back().storedIndex = scrollInputs.size() - 1;
    scrollInputs.back().inputIndex = PREVIOUS;
//    SPRINT
    keyInputs.emplace_back(KeyEvent(sf::Keyboard::LShift));
    keyInputs.back().storedIndex = keyInputs.size() - 1;
    keyInputs.back().inputIndex = SPRINT;


    for (auto &tmp : keyInputs)
        inputs[tmp.inputIndex] = &tmp;
    for (auto &tmp : mouseInputs)
        inputs[tmp.inputIndex] = &tmp;
    for (auto &tmp : scrollInputs)
        inputs[tmp.inputIndex] = &tmp;
}

InputEvent &Input::getEvent(InputIndex index) {
    return *inputs[index];
}

// remapping is not done yet

bool Input::remap(InputIndex index, sf::Keyboard::Key key) {
    for (auto &tmp : this->keyInputs) {
        if (key == tmp.key)
            return false;
    }
    this->keyInputs[inputs[index]->storedIndex] = KeyEvent(key);
    return true;
}

bool Input::remap(InputIndex index, sf::Mouse::Button button) {
    for (auto &tmp : this->mouseInputs) {
        if (button == tmp.button)
            return false;
    }
    this->mouseInputs[inputs[index]->storedIndex] = MouseBtnEvent(button);
    return true;
}

bool Input::remap(InputIndex index, sf::Mouse::Wheel wheel, bool positiveDirection) {
    for (auto &tmp : this->scrollInputs) {
        if (wheel == tmp.wheel && positiveDirection == tmp.positive)
            return false;
    }
    this->scrollInputs[inputs[index]->storedIndex] = ScrollEvent(wheel, positiveDirection);
    return true;
}

void Input::update() {
    for (auto &tmp : inputs)
        tmp->update();
}

void Input::scrollUpdate(sf::Event &event) {
    for (auto &tmp : scrollInputs)
        tmp.scrollUpdate(event);
}

void Input::scrollReset() {
    for (auto &tmp : scrollInputs)
        tmp.releasedBehavior();
}


Input Input::input;