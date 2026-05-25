#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Player
{
private:
    std::optional<sf::Sprite> sprite;        

    float speed;              // Prêdkoœæ chodzenia na boki
    float gravity;            // Si³a grawitacji (jak szybko spada)

    float speedY; //aktualna prêdkoœæ pionowa
    float jumpPower; //si³a skoku
    bool canJump; //czy dotyka ziemi zeby skoczyc

    sf::Clock animClock; // Zegar odmierzaj¹cy czas miêdzy klatkami
    int animFrame = 0;

    sf::IntRect standFrame;
    std::vector<sf::IntRect> walkFrames;
    sf::IntRect jumpFrame;

public:
   
    Player();

    void initTexture(const sf::Texture& texture);

    void update();
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    void stopFalling(float platformTopY);
    void reset();

    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
    void bounceUp();
};