#include "PhysicsManager.hpp"
#include <cmath>
#include "../../physics/VectorMath.hpp"

void RoundLine::UpdateArray() {
    if (array.getVertexCount() != 4)
        array.resize(4);
    array.setPrimitiveType(Lines);
    startShape.setRadius(radius);
    startShape.setPosition(start);
    startShape.setOrigin(radius, radius);

    endShape.setRadius(radius);
    endShape.setPosition(end);
    endShape.setOrigin(radius, radius);

    Vector2f diff = end - start;
    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    array[0].position = Vector2f(start.x - (diff.y / dist) * radius, start.y + (diff.x / dist) * radius);
    array[1].position = Vector2f(end.x - (diff.y / dist) * radius, end.y + (diff.x / dist) * radius);
    array[2].position = Vector2f(start.x + (diff.y / dist) * radius, start.y - (diff.x / dist) * radius);
    array[3].position = Vector2f(end.x + (diff.y / dist) * radius, end.y - (diff.x / dist) * radius);
}

void PhysicsManager::Init() {

}

void PhysicsManager::Update() {
    for (auto &tmp : staticLines) {
        tmp.UpdateArray();
    }
    for (auto &tmp : circles) {
        tmp.vel.y += 0.1f;
        //Vector2f oldPos = tmp.pos;
        tmp.pos += tmp.vel;
        //float dist = Dist(Vector2f(0, 0), tmp.vel);
        //int steps = int(dist / Circle::radius);
        //float remainder = fmodf(dist, Circle::radius);
        //float multiplier = 1.f;
        //for (int i = 0; i <= steps; ++i) {
            //if (i == steps)
                //multiplier = remainder;
            Vector2f hit = Vector2f(0, 0);
            for (auto &line : staticLines) {
                if (CircleLineCheck(tmp, line, hit))
                    CirclePointResponse(tmp, hit);
                /*Vector2f diff = line.end - line.start;
                Vector2f cirDiff = tmp.pos - line.start;
                Vector2f hit = line.start +
                        ((diff.x * cirDiff.x + diff.y * cirDiff.y)/
                        std::pow(std::sqrt(diff.x * diff.x + diff.y * diff.y), 2.f)) * diff;
                Vector2f distV = hit - tmp.pos;
                float dist = distV.x * distV.x + distV.y * distV.y;
                if (dist <= std::pow(RoundLine::radius + Circle::radius, 2.f)) {
                    tmp.vel.y = 0;
                    tmp.vel.x = 0;
                    tmp.pos = hit - Vector2f (0, RoundLine::radius + Circle::radius);
                }*/
            }
        //}
        tmp.shape.setPosition(tmp.pos);
    }
}

void PhysicsManager::Draw(RenderWindow &window) {
    for (const auto &tmp : staticLines) {
        window.draw(tmp.startShape);
        window.draw(tmp.endShape);
        window.draw(tmp.array);
    }
    for (const auto &tmp : circles) {
        window.draw(tmp.shape);
    }
}

void PhysicsManager::CirclePointResponse(Circle &circle, Vector2f point) {
    float offsetRadius = Circle::radius + RoundLine::radius;
    float distX = point.x - circle.pos.x;
    float distY = point.y - circle.pos.y;
    Vector2f normal = Normal(circle.pos, point);
    float distance = std::sqrt((distX * distX) + (distY * distY));
    //AddForce(normal * (1.f / distance) * elasticity);
    //std::cout << distX / distance << "   " << distY / distance << std::endl;
    circle.pos = Vector2f(point.x - distX, point.y - distY);
    Vector2f defaultFloat = Vector2f(0, 0);
    float velMagnitude = Dist(defaultFloat, circle.vel);
    circle.pos = Vector2f(point.x - offsetRadius * (distX / distance), point.y - offsetRadius * (distY / distance));
    Vector2f lineDir = Vector2f(normal.y, -normal.x);
    auto projAL = Vector2f(
            ((circle.vel.x * lineDir.x + circle.vel.y * lineDir.y) / (lineDir.x * lineDir.x + lineDir.y * lineDir.y)) *
            lineDir);
    auto projAN = Vector2f(
            ((circle.vel.x * normal.x + circle.vel.y * normal.y) / (normal.x * normal.x + normal.y * normal.y)) *
            normal);

    circle.vel = circle.elasticity * (projAL -
                                      projAN) /*Vector2f(-velMagnitude * distX / distance + abs(normal.y) * vel.x, -velMagnitude * distY / distance + abs(normal.x) * vel.y)*/
                 + (1.0f - circle.elasticity) *
                   projAL;//Vector2f((lineDir.x * vel.x - lineDir.y * -vel.y) * lineDir.x, (lineDir.x * vel.x - lineDir.y * -vel.y) * lineDir.y);
}

bool PhysicsManager::CircleLineCheck(Circle &circle, RoundLine &line, Vector2f &point) {
    Vector2f diff = line.end - line.start;
    Vector2f cirDiff = circle.pos - line.start;
    Vector2f hit = line.start +
                   ((diff.x * cirDiff.x + diff.y * cirDiff.y) /
                    std::pow(std::sqrt(diff.x * diff.x + diff.y * diff.y), 2.f)) * diff;
    Vector2f distV = hit - circle.pos;
    float dist = distV.x * distV.x + distV.y * distV.y;
    if (dist <= std::pow(RoundLine::radius + Circle::radius, 2.f)) {//needs clamp also
        point = hit;
        return true;
        //circle.vel.y = 0;
        //circle.vel.x = 0;
        //circle.pos = hit - Vector2f (0, RoundLine::radius + Circle::radius);
    }
    return false;
}
