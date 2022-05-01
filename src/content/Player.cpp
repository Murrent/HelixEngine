#include <iostream>
#include "Player.hpp"
#include "../system/Input.hpp"
#include "../scene/GameManager.hpp"

Player::Player(float x, float y, float width, float height) : RectangleObject(x, y, width, height) {
    this->shape.setSize(2.0f * sf::Vector2f(width, height));
    this->shape.setPosition(x, y);
    this->shape.setOrigin(width, height);
    this->inventory.setSize(10, 5);
    this->inventoryOpen = false;
    this->inventory.start();
}

void Player::setPosition(const sf::Vector2f &_position) {
    PhysicsObject::setPosition(_position);
    this->shape.setPosition(_position);
}

void Player::updateInputs() {
    sf::Vector2f vel = this->getVelocity();
    if (Input::input.getEvent(LEFT).getActive())
        vel.x -= 0.04f;
    if (Input::input.getEvent(RIGHT).getActive())
        vel.x += 0.04f;

    if (Input::input.getEvent(JUMP).getDown())
        vel.y -= 0.6f;
    else
        vel.y += 0.02f;

    vel.x *= 0.8f;
    vel.y *= 0.99f;

    this->setVelocity(vel);

    if (Input::input.getEvent(INVENTORY).getDown())
        inventoryOpen = !inventoryOpen;

    hotbar.items = inventory.getHotbarItems();
    hotbar.update();
    if (inventoryOpen)
        inventory.update();
    else {
        equippedItem = hotbar.getSelectedItem();
        if (equippedItem != nullptr) {
            if (Input::input.getEvent(TRIGGER).getActive())
                equippedItem->Use();
            else if (Input::input.getEvent(TRIGGER2).getActive())
                equippedItem->Use2();
            else if (Input::input.getEvent(DROPITEM).getActive()) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(GameManager::window);
                sf::Vector2f worldPos = GameManager::window.mapPixelToCoords(mousePos);
                hotbar.dropEquippedItem(worldPos);
            }
        }
    }

}

void Player::draw() {
    Entity::draw();
    GameManager::window.draw(this->shape);

    if (inventoryOpen) this->inventory.draw();
    else hotbar.draw();
}
