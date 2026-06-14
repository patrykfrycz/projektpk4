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

bool Button::update(const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

    bool justHovered = false; 

    if (sprite.has_value()) {
        if (sprite->getGlobalBounds().contains(worldPos)) {
            sprite->setScale({ 1.05f, 1.05f });

            if (!wasHovered) {
                justHovered = true;
                wasHovered = true;  
            }
        }
        else {
            sprite->setScale({ 1.0f, 1.0f });
            wasHovered = false; 
        }
    }
    return justHovered;
}