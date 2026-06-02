#include "Button.h"

Button::Button(float x, float y) {
    position = { x, y };
}

void Button::initTexture(const sf::Texture& texture) {
    sprite.emplace(texture);
    sprite->setPosition(position);

}

void Button::draw(sf::RenderWindow& window) {
    if (sprite.has_value()) {
        window.draw(*sprite);
    }
}

bool Button::isClicked(const sf::RenderWindow& window) const {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        if (sprite.has_value() && sprite->getGlobalBounds().contains(worldPos)) {
            return true;
        }
    }
    return false;
}