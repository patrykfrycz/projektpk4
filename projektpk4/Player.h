#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::RectangleShape shape; // Kszta³t gracza 
    float speed;              // Prêdkoœæ chodzenia na boki
    float gravity;            // Si³a grawitacji (jak szybko spada)

public:
    // Konstruktor - ustawi pozycjê startow¹ gracza
    Player();

    // Metoda licz¹ca fizykê i sprawdzaj¹ca klawiaturê
    void update();

    // Metoda rysuj¹ca gracza na oknie
    void draw(sf::RenderWindow& window);
};