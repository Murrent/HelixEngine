#include "Camera.hpp"
#include "../scene/GameManager.hpp"
#include "Animation.hpp"

// CamView

CamView::CamView() {

}

CamView::CamView(sf::Vector2f _target, float _zoom, float _scale, float _moveSpeed) :
        target(_target), zoom(_zoom), scale(_scale), moveSpeed(_moveSpeed) {
    this->view.setCenter(sf::Vector2f(0, 0));
    this->view.setSize((sf::Vector2f) GameManager::window.getSize());
}

// Camera

Camera::Camera() {
    this->target = sf::Vector2f(0.0f, 0.0f);
    this->uiView.setCenter(sf::Vector2f(0, 0));
    this->uiView.setSize((sf::Vector2f) GameManager::window.getSize());
    this->scale = this->uiView.getSize().y * 0.08f;

    this->worldView.setSize(sf::Vector2f(80, 40));
    this->worldView.setCenter(sf::Vector2f(0, 0));
}

void Camera::staticUI() {
    sf::View tmpView(sf::Vector2f(0, 0), (sf::Vector2f) GameManager::window.getSize());
    this->scale = tmpView.getSize().y * 0.08f;
    GameManager::window.setView(this->uiView);
}

void Camera::worldCam() {
    this->worldView.setSize(64.f * static_cast<float>(GameManager::window.getSize().x) / 2000.f,
                            32.f * static_cast<float>(GameManager::window.getSize().y) / 1000.f);
    this->zoomWorld = 1.0f;

    this->worldView.setCenter(LerpV2(this->worldView.getCenter(), this->target, this->moveSpeed));
    GameManager::window.setView(this->worldView);
}

