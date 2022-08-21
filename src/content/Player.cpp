#include <iostream>
#include "Player.hpp"
#include "../system/Input.hpp"
#include "../scene/GameManager.hpp"
#include "../common/Animation.hpp"

Player::Player(float x, float y, float width, float height) : RectangleObject(x, y, width, height) {
    shape.setSize(2.0f * sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setOrigin(width, height);
    inventory.setSize(10, 5);
    inventoryOpen = false;
    inventory.start();
}

void Player::setPosition(const sf::Vector2f &_position) {
    PhysicsObject::setPosition(_position);
}

void Player::updateInputs() {
    if (Input::input.getEvent(LEFT).getActive())
        leftInput = true;
    if (Input::input.getEvent(RIGHT).getActive())
        rightInput = true;

    if (Input::input.getEvent(JUMP).getDown())
        jumpInput = true;

    if (Input::input.getEvent(INVENTORY).getDown()) {
        inventoryOpen = !inventoryOpen;
        inventory.close();
    }

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

    hotbar.items = inventory.getHotbarItems();
}

void Player::draw() {
    Entity::draw();
    shape.setPosition(LerpV2(shape.getPosition(), PhysicsObject::getPosition(), 0.5f));
    GameManager::window.draw(shape);

    if (inventoryOpen) inventory.draw();
    else hotbar.draw();
}

void Player::physicsUpdate() {
    PhysicsObject::physicsUpdate();
    sf::Vector2f vel = this->getVelocity();
    if (leftInput) {
        vel.x -= 0.04f;
        leftInput = false;
    }
    if (rightInput) {
        vel.x += 0.04f;
        rightInput = false;
    }

    if (jumpInput) {
        vel.y -= 0.6f;
        jumpInput = false;
    } else {
        vel.y += 0.02f;
    }

    vel.x *= 0.8f;
    vel.y *= 0.99f;

    setVelocity(vel);
}
