#pragma once
#include "Item.h"
#include "Platform.h"
#include <SFML/Graphics.hpp>
#include <optional>

class Star : public Item {
private:
    std::optional<sf::Sprite> sprite;
    sf::Vector2f vecspeed;

public:
    Star(float x, float y);

    void initTexture(const sf::Texture& texture);

    void update() override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;

    void resolveCollision(const Platform& platform);
};