#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Platform {
private:
    sf::RectangleShape rect;
    sf::Vector2f baseSize{ 0.f, 50.f };
    float marginBottom = 0.f;
    bool stretchFullWidth = true;
    float leftX = 0.f;

public:
    Platform(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::Yellow);

    Platform(float height, float marginFromBottom = 0.f, const sf::Color& color = sf::Color::Yellow,
        bool stretchToFullWidth = true, float leftX = 0.f, float requestedWidth = 0.f);

    void update(const sf::RenderWindow& window);

    // Rysowanie platformy
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;

    void setColor(const sf::Color& color);
    void setMarginBottom(float margin);
    void setStretchFullWidth(bool stretch);
};