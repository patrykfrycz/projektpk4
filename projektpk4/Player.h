#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Player
{
private:
    sf::RectangleShape shape; // Kszta³t gracza 
    float speed = 2000.f;              // Prêdkoœæ chodzenia na boki
    const float gravity = 1200.f;  // Si³a grawitacji (jak szybko spada)
    sf::Vector2f velocity{ 0.f, 0.f };

public:
    // Konstruktor - ustawi pozycjê startow¹ gracza
    Player(const sf::Vector2f& size = { 64.f, 64.f }, const sf::Vector2f& startPos = { 100.f, 100.f });

    // Metoda licz¹ca fizykê i sprawdzaj¹ca klawiaturê
    void update(float dt, const std::vector<sf::FloatRect>& platforms);

    // Metoda rysuj¹ca gracza na oknie
    void draw(sf::RenderWindow& window);
};