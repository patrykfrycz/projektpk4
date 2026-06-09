#include "Flag.h"

Flag::Flag(float x, float y) : position(x, y) {}

void Flag::initTexture(const sf::Texture& texture) {
    sprite.emplace(texture);
    sprite->setPosition(position);
}

void Flag::draw(sf::RenderWindow& window) {
    if (sprite.has_value()) {
        window.draw(*sprite);
    }
}

sf::FloatRect Flag::getBounds() const {
    if (sprite.has_value()) {
        return sprite->getGlobalBounds();
    }
    return sf::FloatRect(position, { 50.f, 400.f });
}
