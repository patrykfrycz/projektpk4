#include "Enemy.h"
#include "Platform.h" 

Enemy::Enemy(sf::Texture& texture, sf::Vector2f startPos, int frameWidth, int frameHeight, EnemyType type) : sprite(texture), type(type) {
    

    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { frameWidth, frameHeight }));
    sprite.setPosition(startPos);
    sprite.setScale({ 2.5f, 2.5f });

    walkSpeed = -100.f;
    gravity = 400.f; 

    vecspeed = { walkSpeed, 0.f };
}

void Enemy::update(float deltaTime) {
    if (squashed) {
        deathTimer += deltaTime;
        return; 
    }

    vecspeed.y += gravity * deltaTime;

    sprite.move(vecspeed * deltaTime);
}

void Enemy::bounce() {
    vecspeed.x = -vecspeed.x;
}

void Enemy::resolveCollision(const Platform& platform) {
    auto intersectionOpt = getBounds().findIntersection(platform.getBounds());

    if (intersectionOpt.has_value()) {
        sf::FloatRect inter = intersectionOpt.value();
        sf::FloatRect pBounds = platform.getBounds();
        sf::FloatRect eBounds = getBounds();

        if (inter.size.x < inter.size.y) {
            if (vecspeed.x > 0) {
                sprite.setPosition({ pBounds.position.x - eBounds.size.x - 0.1f, sprite.getPosition().y });
            }
            else {
                sprite.setPosition({ pBounds.position.x + pBounds.size.x + 0.1f, sprite.getPosition().y });
            }

            bounce();
        }
        else {
            if (vecspeed.y > 0 && eBounds.position.y < pBounds.position.y) {
                sprite.setPosition({ sprite.getPosition().x, pBounds.position.y - eBounds.size.y });
                vecspeed.y = 0.f;
            }
        }
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}

void Enemy::squash() {
    squashed = true;
    vecspeed = { 0.f, 0.f };

    float oldHeight = getBounds().size.y;

    if (type == EnemyType::Goomba) {
        sprite.setTextureRect(sf::IntRect({ 57, 16 }, { 18, 6 }));
    }
    else if (type == EnemyType::Troopa) {
        sprite.setTextureRect(sf::IntRect({ 36, 7 }, { 16, 15 }));
    }

    float newHeight = getBounds().size.y;
    sprite.move({ 0.f, oldHeight - newHeight }); 
}

bool Enemy::isSquashed() const {
    return squashed;
}

bool Enemy::isReadyToRemove() const {
    return (squashed && deathTimer >= 0.25f);
}