#pragma once


#include <SFML/Graphics/View.hpp>

class CamView {
public:
    sf::View view;
    sf::Vector2f target;
    float zoom{}, scale{};
    float moveSpeed{};

    CamView();

    CamView(sf::Vector2f _target, float _zoom, float _scale, float _moveSpeed);
};

class Camera {
public:
    float zoomUI, zoomWorld, scale;
    float moveSpeed;
    sf::Vector2f target;
    sf::View uiView, worldView;

    Camera();

    void staticUI();

    void worldCam();
};

Camera mainCamera;