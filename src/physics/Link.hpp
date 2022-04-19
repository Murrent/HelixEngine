#pragma once


#include <vector>
#include "VerletObject.hpp"
#include "VectorMath.hpp"

class Link {
public:
    u_int32_t object1;
    u_int32_t object2;
    float targetDistance;

    void apply(std::vector<VerletObject>& objects) {
        VerletObject& obj1 = objects[object1];
        VerletObject& obj2 = objects[object2];
        const sf::Vector2f axis = obj1.position - obj2.position;
        const float dist = Dist(sf::Vector2f(0, 0), axis);
        const sf::Vector2f n = axis / dist;
        const float scale = 1 / (obj1.size * obj1.size + obj2.size * obj2.size);
        if (targetDistance < dist * 0.95f){
            const float delta = targetDistance - dist * 0.95f;
            obj1.position += scale * obj2.size * obj2.size * delta * n;
            obj2.position -= scale * obj1.size * obj1.size * delta * n;
        }else if(targetDistance > dist * 1.05f){
            const float delta = targetDistance - dist * 1.05f;
            obj1.position += scale * obj2.size * obj2.size * delta * n;
            obj2.position -= scale * obj1.size * obj1.size * delta * n;
        }
    }
};

class RigidObject {
    std::vector<u_int32_t> objects;
    std::vector<float> distances;
    sf::Vector2f com;
    
    void calculateCOM(std::vector<VerletObject>& objs) {
        com = {};
        for (int i = 0; i < objects.size(); ++i) {
            com += objs[i].position;
        }
        com /= (float)objects.size();
    }
    
    void apply(std::vector<VerletObject>& objs) {
        
    }
};