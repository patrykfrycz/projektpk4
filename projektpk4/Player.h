#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::RectangleShape shape; // Kszta³t gracza 
    float speed;              // Prêdkoœæ chodzenia na boki
    float gravity;            // Si³a grawitacji (jak szybko spada)

    float speedY; //aktualna prêdkoœæ pionowa
    float jumpPower; //si³a skoku
    bool canJump; //czy dotyka ziemi zeby skoczyc


public:
    // Konstruktor - ustawi pozycjê startow¹ gracza
    Player();

    // Metoda licz¹ca fizykê i sprawdzaj¹ca klawiaturê
    void update();

    // Metoda rysuj¹ca gracza na oknie
    void draw(sf::RenderWindow& window);

    // Kolizje
    sf::FloatRect getBounds() const;

    // Metoda do zaprzestania spadania dzieki kolizji z platforma
    void stopFalling(float platformTopY);

    void reset();

    float getX() const;
    float getY() const;

    void setX(float x);
};