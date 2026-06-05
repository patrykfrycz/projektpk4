#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "Player.h"

class Platform {
protected:
    std::optional<sf::Sprite> sprite;
    sf::Vector2f initialPosition;
    sf::Vector2f size; // Zmienna do zapamiêtania wymiarów ca³ej platformy
public:
    Platform(float x, float y, float width, float height);

    void initTexture(const sf::Texture& texture);

    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

    void resetPlatform();

    void resolveCollision(Player& player) const;
};