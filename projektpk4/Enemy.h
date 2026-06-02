#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

enum class EnemyType {
    Goomba,
    Troopa
};

class Enemy {
private:
    sf::Sprite sprite;
    sf::Vector2f vecspeed;
    float walkSpeed;
    float gravity;

    bool squashed = false;
    float deathTimer = 0.f;

    EnemyType type;

public:
    Enemy(sf::Texture& texture, sf::Vector2f startPos, int frameWidth, int frameHeight, EnemyType type);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void bounce();
    sf::FloatRect getBounds() const;

    void resolveCollision(const Platform& platform);

    void squash();
    bool isSquashed() const;
    bool isReadyToRemove() const;
};