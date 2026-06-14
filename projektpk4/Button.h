#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Button {
private:
    std::optional<sf::Sprite> sprite;
    sf::Vector2f position; 
    bool wasHovered = false;
public:
    Button(float x, float y);

    void initTexture(const sf::Texture& texture);

    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::RenderWindow& window) const;

    bool update(const sf::RenderWindow& window);
};