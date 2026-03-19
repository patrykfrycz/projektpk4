#include "Button.h"

Button::Button(){
	shape.setSize({ 200.f, 40.f });
	shape.setFillColor(sf::Color::White);
	shape.setPosition({ 400.f, 400.f });
}

// 2. Rysowanie przycisku
void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
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