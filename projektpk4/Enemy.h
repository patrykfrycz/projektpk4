#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
private:
    sf::Sprite sprite;
    sf::Vector2f vecspeed;
    float walkSpeed;

public:
    // Konstruktor: ustawia teksturê i pozycjê startow¹
    Enemy(sf::Texture& texture, sf::Vector2f startPos);

    // Aktualizacja logiki (ruch)
    void update(float deltaTime);

    // Rysowanie w oknie
    void draw(sf::RenderWindow& window);

    // Funkcja do odbijania moba od œcian
    void bounce();

    // Pobranie granic sprite'a (przydatne do kolizji)
    sf::FloatRect getBounds() const;
};