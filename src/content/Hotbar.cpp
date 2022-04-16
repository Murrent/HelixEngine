#include "Hotbar.hpp"

Hotbar::Hotbar() : size(0), selected(0) {}

Hotbar::Hotbar(unsigned int slots, unsigned int selectedSlot) : size(slots), selected(selectedSlot) {}

void Hotbar::update() {
    Entity::update();
}

void Hotbar::draw() {
    Entity::draw();
}


