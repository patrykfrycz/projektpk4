#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

enum class EnemyType {
    Goomba,
    Troopa
};


class Enemy {
protected: 
    sf::Sprite sprite;
    sf::Vector2f vecspeed;
    float walkSpeed;
    float gravity;

    bool squashed = false;
    float deathTimer = 0.f;

    EnemyType type;

    bool shellMoving = false;
    bool completelyDead = false;
    bool knockedOut = false;
    bool onGround = false;
    sf::FloatRect currentPlatformBounds;

public:
    Enemy(sf::Texture& texture, sf::Vector2f startPos, int frameWidth, int frameHeight, EnemyType type);

    virtual ~Enemy() = default;

    virtual void update(float deltaTime);
    virtual void squash() = 0; 
    virtual bool isReadyToRemove() const;

    void draw(sf::RenderWindow& window);
    void bounce();
    sf::FloatRect getBounds() const;
    void resolveCollision(const sf::FloatRect& pBounds);

    bool isSquashed() const;
    EnemyType getType() const;
    bool isShellMoving() const;
    void kick(float marioX);
    void setDead();
    void knockOut();
    bool isKnockedOut() const;
};


class Goomba : public Enemy {
public:
    Goomba(sf::Texture& texture, sf::Vector2f startPos);
    void update(float deltaTime) override;
    void squash() override;
    bool isReadyToRemove() const override;
};

class Troopa : public Enemy {
public:
    Troopa(sf::Texture& texture, sf::Vector2f startPos);
    void update(float deltaTime) override;
    void squash() override;
};