#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Platform.h"

Platform::Platform(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color)
    : baseSize(size), marginBottom(0.f), stretchFullWidth(false), leftX(position.x)
{
    rect.setSize({ 200.f, 800.f });
    rect.setFillColor(sf::Color::Blue);
    rect.setPosition({ 0, 800 });
}

Platform::Platform(float height, float marginFromBottom, const sf::Color& color,
    bool stretchToFullWidth, float leftX_, float requestedWidth)
    : baseSize(requestedWidth > 0.f ? sf::Vector2f(requestedWidth, height) : sf::Vector2f(0.f, height)),
      marginBottom(marginFromBottom),
      stretchFullWidth(stretchToFullWidth),
      leftX(leftX_)
{
    rect.setSize(stretchFullWidth ? sf::Vector2f(100.f, height) : baseSize);
    rect.setFillColor(color);
}

void Platform::update(const sf::RenderWindow& window)
{
    sf::Vector2u ws = window.getSize();

    float width = stretchFullWidth ? static_cast<float>(ws.x)
                                   : (baseSize.x > 0.f ? baseSize.x : static_cast<float>(ws.x) - 2.f * leftX);

    float height = baseSize.y > 0.f ? baseSize.y : rect.getSize().y;

    rect.setSize({ width, height });

    float x = stretchFullWidth ? 0.f : leftX;
    float y = static_cast<float>(ws.y) - height - marginBottom;

    rect.setPosition({ x , y });
}

void Platform::draw(sf::RenderWindow& window) const
{
    window.draw(rect);
}

sf::FloatRect Platform::getBounds() const
{
    return rect.getGlobalBounds();
}

void Platform::setColor(const sf::Color& color) { rect.setFillColor(color); }
void Platform::setMarginBottom(float margin) { marginBottom = margin; }
void Platform::setStretchFullWidth(bool stretch) { stretchFullWidth = stretch; }