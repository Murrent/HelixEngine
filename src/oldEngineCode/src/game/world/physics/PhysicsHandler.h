//
// Created by Martin on 2021-01-02.
//

#ifndef GAMEENGINE_PHYSICSHANDLER_H
#define GAMEENGINE_PHYSICSHANDLER_H
#include "Shape.h"
#include <vector>

class PhysicsHandler {
public:
    std::vector<Shape*> shapes;
    void Update(float delta);
};


#endif //GAMEENGINE_PHYSICSHANDLER_H
