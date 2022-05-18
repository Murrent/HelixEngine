#include <cstdio>
#include "system/Engine.hpp"
#include <iostream>
#include "noise/SimplexNoise.hpp"

//class Data {
//public:
//    int a;
//    int b;
//    bool c;
//
//    Data() {
//        a = 1;
//        b = 2;
//        c = true;
//    }
//};
//
//class Shitty : public Entity {
//
//};

int main() {
    for (float i = 0; i < 1; i += 0.005f) {
        auto x = i;                   // Define a float coordinate
        float noise = SimplexNoise::noise(x);   // Get the noise value for the coordinate
        std::cout << noise << std::endl;
    }
//    b2Vec2 gravity(0.0f, -10.0f);
//
//    b2World world(gravity);
//
//    b2BodyDef groundBodyDef;
//    groundBodyDef.position.Set(0.0f, -10.0f);
//
//    b2Body* groundBody = world.CreateBody(&groundBodyDef);
//
//    b2PolygonShape groundBox;
//    groundBox.SetAsBox(50.0f, 10.0f);
//
//    groundBody->CreateFixture(&groundBox, 0.0f);
//
//    b2BodyDef bodyDef;
//    bodyDef.type = b2_dynamicBody;
//    bodyDef.position.Set(0.0f, 4.0f);
//    b2Body* body = world.CreateBody(&bodyDef);
//
//    b2PolygonShape dynamicBox;
//    dynamicBox.SetAsBox(1.0f, 1.0f);
//
//    b2FixtureDef fixtureDef;
//    fixtureDef.shape = &dynamicBox;
//    fixtureDef.density = 1.0f;
//    fixtureDef.friction = 0.3f;
//
//    body->CreateFixture(&fixtureDef);
//
//    float timeStep = 1.0f / 60.0f;
//
//    int32 velocityIterations = 6;
//    int32 positionIterations = 2;
//
//    for (int32 i = 0; i < 60; ++i)
//    {
//        world.Step(timeStep, velocityIterations, positionIterations);
//        b2Vec2 position = body->GetPosition();
//        float angle = body->GetAngle();
//        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
//    }

//    Shitty* shit = engine.NewEntity<Shitty>();
//    delete shit;

//    Data data = Data();
//
//    data.a = 7;
//    data.b = 6;
//    data.c = false;
//    printf("%d %d %d %d\n", sizeof(data.a), sizeof(data.b), sizeof(data.c), sizeof(data));
//    printf("%d %d %d\n", data.a, data.b, data.c);
//
//    FILE* file = fopen("data_save", "wb");
//
//    fwrite(&data, sizeof(Data), 1, file);
//
//    fclose(file);
//
//    data.a = 5;
//    data.b = 3;
//    data.c = true;
//
//    printf("%d %d %d\n", data.a, data.b, data.c);
//
//    FILE* filer = fopen("data_save", "rb");
//    while (fread(&data, sizeof(Data), 1, filer)) {
//        printf("%d %d %d\n", data.a, data.b, data.c);
//    }
//    fclose(file);

    return 0;
}