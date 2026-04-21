#include "Platform.h"

Platform::Platform(float x, float y, float width, float height) {
    shape.setPosition({ x, y });
    shape.setSize({ width, height });
    shape.setFillColor(sf::Color::Green);
}

void Platform::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Platform::getBounds() const {
    return shape.getGlobalBounds();
}

void Platform::resetPlatform() {
    shape.setPosition({0.f, 500.f});
}