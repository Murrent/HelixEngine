#pragma once

#include <vector>
#include "Entity.hpp"

class Engine {
private:
    std::vector<Entity *> entities;

public:
    template<class T>
    T *NewEntity();
};

template<class T>
T *Engine::NewEntity() {
    static_assert(std::is_base_of<Entity, T>::value, "Class does not derive from Entity");
    T* tmp = new T();
    entities.push_back(tmp);
    return tmp;
}

static Engine engine;

