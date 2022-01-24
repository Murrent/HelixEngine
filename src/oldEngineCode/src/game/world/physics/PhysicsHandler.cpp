//
// Created by Martin on 2021-01-02.
//

#include "PhysicsHandler.h"

void PhysicsHandler::Update(float delta) {
    for (auto & shape : shapes) {
        shape->Update(delta);
    }
}
