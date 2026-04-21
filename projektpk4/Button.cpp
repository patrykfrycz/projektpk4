#include "Button.h"


Button::Button(float x, float y, float tx, float ty, const sf::Font& font, std::string buttonText) : text(font) {
    shape.setSize({ 220.f, 40.f });
    shape.setFillColor(sf::Color::White);
    shape.setPosition({ x, y });

    //napis na przycisku
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black); // Czarny napis na bia³ym tle
    text.setPosition({ tx, ty });
}

// 2. Rysowanie przycisku
void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

// 3. Sprawdzanie, czy myszka w niego kliknê³a
bool Button::isClicked(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    sf::FloatRect btnArea = shape.getGlobalBounds();

    if (btnArea.contains(sf::Vector2f(mousePos))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            return true;
        }
    }

    return false;
}