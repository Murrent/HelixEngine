#include "PhysicsManager.hpp"
#include "../scene/GameManager.hpp"
#include "ItemObject.hpp"
#include <cmath>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

// Going too fast into to the right into the wall will get you stuck
// but this is very low chance, since it requires pixel perfect precision and very high speeds

bool PhysicsManager::checkLeftVel(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation,
                                  sf::Vector2i &tile) {
    for (unsigned int x = 0; x < tileOccupation.x; ++x) {
        if (x == 0)
            tile.x = std::floor(btmRight.x);
        else if (x == tileOccupation.x - 1)
            tile.x = std::floor(topLeft.x);
        else
            tile.x = std::floor(btmRight.x - float(x));

        for (unsigned int y = 0; y < tileOccupation.y; ++y) {
            if (y == 0)
                tile.y = std::floor(topLeft.y);
            else if (y == tileOccupation.y - 1)
                tile.y = std::floor(btmRight.y);
            else
                tile.y = std::floor(topLeft.y + float(y));

            if (GameManager::map.getTileType(tile.x, tile.y) != 0) {
                return true;
            }
        }
    }
    tile = sf::Vector2i(0, 0);
    return false;
}

bool PhysicsManager::checkRightVel(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation,
                                   sf::Vector2i &tile) {
    for (unsigned int x = 0; x < tileOccupation.x; ++x) {
        if (x == 0)
            tile.x = std::floor(topLeft.x);
        else if (x == tileOccupation.x - 1)
            tile.x = std::floor(btmRight.x);
        else
            tile.x = std::floor(topLeft.x + float(x));

        for (unsigned int y = 0; y < tileOccupation.y; ++y) {
            if (y == 0)
                tile.y = std::floor(topLeft.y);
            else if (y == tileOccupation.y - 1)
                tile.y = std::floor(btmRight.y);
            else
                tile.y = std::floor(topLeft.y + float(y));

            if (GameManager::map.getTileType(tile.x, tile.y) != 0) {
                return true;
            }
        }
    }
    tile = sf::Vector2i(0, 0);
    return false;
}

bool PhysicsManager::checkUpVel(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation,
                                sf::Vector2i &tile) {
    for (unsigned int y = 0; y < tileOccupation.y; ++y) {
        if (y == 0)
            tile.y = std::floor(btmRight.y);
        else if (y == tileOccupation.y - 1)
            tile.y = std::floor(topLeft.y);
        else
            tile.y = std::floor(btmRight.y - float(y));

        for (unsigned int x = 0; x < tileOccupation.x; ++x) {
            if (x == 0)
                tile.x = std::floor(topLeft.x);
            else if (x == tileOccupation.x - 1)
                tile.x = std::floor(btmRight.x);
            else
                tile.x = std::floor(topLeft.x + float(x));

            if (GameManager::map.getTileType(tile.x, tile.y) != 0) {
                return true;
            }
        }
    }
    tile = sf::Vector2i(0, 0);
    return false;
}

bool PhysicsManager::checkDownVel(sf::Vector2f topLeft, sf::Vector2f btmRight, sf::Vector2u tileOccupation,
                                  sf::Vector2i &tile) {
    for (unsigned int y = 0; y < tileOccupation.y; ++y) {
        if (y == 0)
            tile.y = std::floor(topLeft.y);
        else if (y == tileOccupation.y - 1)
            tile.y = std::floor(btmRight.y);
        else
            tile.y = std::floor(topLeft.y + float(y));

        for (unsigned int x = 0; x < tileOccupation.x; ++x) {
            if (x == 0)
                tile.x = std::floor(topLeft.x);
            else if (x == tileOccupation.x - 1)
                tile.x = std::floor(btmRight.x);
            else
                tile.x = std::floor(topLeft.x + float(x));

            if (GameManager::map.getTileType(tile.x, tile.y) != 0) {
                return true;
            }
        }
    }
    tile = sf::Vector2i(0, 0);
    return false;
}


bool PhysicsManager::continousRectCheckX(RectangleObject &obj, sf::Vector2f dest, sf::Vector2u tileOccupation) {
    if (obj.getVelocity().x == 0.0f) return false;
    const sf::Vector2f &pos = obj.getPosition();
    float size2 = obj.getSize().x * 2.0f;
    if (size2 == 0.0f) return false;
    unsigned int xSteps = std::ceil(std::abs(dest.x - pos.x) / size2);
    bool positiveX;
    if (obj.getVelocity().x > 0.0f) positiveX = true;
    else positiveX = false;
    float tmpX;

    for (unsigned int i = 1; i <= xSteps; ++i) {
        if (i == xSteps)
            tmpX = dest.x;
        else if (positiveX)
            tmpX = pos.x + float(i) * size2;
        else
            tmpX = pos.x - float(i) * size2;

        sf::Vector2f topLeft = sf::Vector2f(tmpX, pos.y) - obj.getSize();
        sf::Vector2f btmRight = sf::Vector2f(tmpX, pos.y) + obj.getSize();
        sf::Vector2i outTile;
        if (positiveX) {
            if (checkRightVel(topLeft, btmRight, tileOccupation, outTile)) {
                obj.setPosition(sf::Vector2f(float(outTile.x) - obj.getSize().x - 0.0001f, pos.y));
                return true;
            }
        } else {
            if (checkLeftVel(topLeft, btmRight, tileOccupation, outTile)) {
                obj.setPosition(sf::Vector2f(float(outTile.x) + obj.getSize().x + 1.0001f, pos.y));
                return true;
            }
        }
    }
    return false;
}

bool PhysicsManager::continousRectCheckY(RectangleObject &obj, sf::Vector2f dest, sf::Vector2u tileOccupation) {
    if (obj.getVelocity().y == 0.0f) return false;
    const sf::Vector2f &pos = obj.getPosition();
    float size2 = obj.getSize().y * 2.0f;
    if (size2 == 0.0f) return false;
    unsigned int ySteps = std::ceil(std::abs(dest.y - pos.y) / size2);
    bool positiveY;
    if (obj.getVelocity().y > 0.0f) positiveY = true;
    else positiveY = false;
    float tmpY;
    for (unsigned int i = 1; i <= ySteps; ++i) {
        if (i == ySteps)
            tmpY = dest.y;
        else if (positiveY)
            tmpY = pos.y + float(i) * size2;
        else
            tmpY = pos.y - float(i) * size2;

        sf::Vector2f topLeft = sf::Vector2f(pos.x, tmpY) - obj.getSize();
        sf::Vector2f btmRight = sf::Vector2f(pos.x, tmpY) + obj.getSize();
        sf::Vector2i outTile;
        if (positiveY) {
            if (checkDownVel(topLeft, btmRight, tileOccupation, outTile)) {
                obj.setPosition(sf::Vector2f(pos.x, float(outTile.y) - obj.getSize().y - 0.0001f));
                return true;
            }
        } else {
            if (checkUpVel(topLeft, btmRight, tileOccupation, outTile)) {
                obj.setPosition(sf::Vector2f(pos.x, float(outTile.y) + obj.getSize().y + 1.0001f));
                return true;
            }
        }
    }
    return false;
}

void PhysicsManager::rectTilemap(RectangleObject &obj) {
    const sf::Vector2f &pos = obj.getPosition();
    sf::Vector2f nextPos = pos + obj.getVelocity();
    sf::Vector2u occupation = sf::Vector2u(std::ceil(obj.getSize().x * 2.0f) + 1,
                                           std::ceil(obj.getSize().y * 2.0f) + 1);

    sf::Vector2f topLeft = pos - obj.getSize();
    sf::Vector2f btmRight = pos + obj.getSize();
    sf::Vector2i outTile;
    if (checkDownVel(topLeft, btmRight, occupation, outTile)) {
        obj.setVelocity(sf::Vector2f(0.0f, 0.0f));
        return;
    }

    sf::Vector2f newPos = pos;

    if (!continousRectCheckX(obj, nextPos, occupation)) {
        obj.setPosition(sf::Vector2f(nextPos.x, obj.getPosition().y));
    } else {
        obj.setVelocity(sf::Vector2f(0.0f, obj.getVelocity().y));
    }
    nextPos = obj.getPosition() + sf::Vector2f(0.0f, obj.getVelocity().y);
    if (!continousRectCheckY(obj, nextPos, occupation)) {
        obj.setPosition(sf::Vector2f(obj.getPosition().x, nextPos.y));
    } else {
        obj.setVelocity(sf::Vector2f(obj.getVelocity().x, 0.0f));
    }
}

void PhysicsManager::circleTilemap(CircleObject &obj) {

}

void PhysicsManager::start() {
    Entity::start();
}

void PhysicsManager::updatePhysics() {
    for (auto &tmp: players){
        tmp->physicsUpdate();
        rectTilemap(*tmp);
    }
    for (auto &tmp: stdRects){
        tmp->physicsUpdate();
        rectTilemap(*tmp);
    }
    for (unsigned int i = 0; i < itemRects.size(); i++) {
        auto &tmp = itemRects[i];
        tmp.setVelocity(tmp.getVelocity() + gravity);
        tmp.physicsUpdate();
        rectTilemap(tmp);
        if (tmp.clock.getElapsedTime().asSeconds() > ItemObject::noPickupTime) {
            for (auto &player: players) {
                sf::Rect<float> playerRect(player->getPosition() - player->getSize(), player->getSize() * 2.0f),
                        itemRect(tmp.getPosition() - tmp.getSize(), tmp.getSize() * 2.0f);

                if (playerRect.intersects(itemRect)) {
                    if (player->inventory.addItem(tmp.item)) {
                        itemRects.erase(itemRects.begin() + i);
                        i--;
                    }
                }
            }
        }
    }
    for (auto &tmp: circles){
        tmp->physicsUpdate();
        circleTilemap(*tmp);
    }
}

void PhysicsManager::update() {
    float timeNow = tickClock.getElapsedTime().asSeconds();
    while (timeNow > timeHandled + updateDelay) {
        timeHandled += updateDelay;
        updatePhysics();
    }
}

void PhysicsManager::draw() {
    Entity::draw();
    for (auto &tmp: itemRects)
        tmp.draw();
}

void PhysicsManager::addStdRect(RectangleObject *obj) {
    stdRects.push_back(obj);
}

void PhysicsManager::addItem(Item *item, float x, float y) {
    this->itemRects.emplace_back(item, x, y);
}

void PhysicsManager::addItem(Item *item, float x, float y, float velX, float velY) {
    this->itemRects.emplace_back(item, x, y, velX, velY);
}



