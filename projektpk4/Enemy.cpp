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
    if (knockedOut) {
        vecspeed.y += gravity * deltaTime;
        sprite.move({ 0.f, vecspeed.y * deltaTime });
        return;
    }

    if (squashed && type == EnemyType::Goomba) {
        deathTimer += deltaTime;
        return;
    }
    if (squashed && type == EnemyType::Troopa && !shellMoving) {
        vecspeed.y += gravity * deltaTime;
        sprite.move({ 0.f, vecspeed.y * deltaTime });
        return;
    }


    if (onGround && !shellMoving) {
        sf::FloatRect eBounds = getBounds();

        if (vecspeed.x < 0 && eBounds.position.x <= currentPlatformBounds.position.x) {
            bounce();
        }
        else if (vecspeed.x > 0 && eBounds.position.x + eBounds.size.x >= currentPlatformBounds.position.x + currentPlatformBounds.size.x) {
            bounce();
        }
    }

    vecspeed.y += gravity * deltaTime;
    sprite.move(vecspeed * deltaTime);

    onGround = false;
}

bool Enemy::isReadyToRemove() const {
    if (knockedOut && sprite.getPosition().y > 800.f) return true;
    if (completelyDead) return true;
    if (type == EnemyType::Troopa) return false;
    return (squashed && deathTimer >= 0.25f);
}

void Enemy::setDead() {
    completelyDead = true;
}

void Enemy::bounce() {
    vecspeed.x = -vecspeed.x;

    sprite.scale({ -1.f, 1.f });

    if (vecspeed.x > 0) {
        sprite.move({ sprite.getGlobalBounds().size.x, 0.f });
    }
    else {
        sprite.move({ -sprite.getGlobalBounds().size.x, 0.f });
    }
}

void Enemy::resolveCollision(const sf::FloatRect& pBounds) {
    if (knockedOut) return;

    auto intersectionOpt = getBounds().findIntersection(pBounds);

    if (intersectionOpt.has_value()) {
        sf::FloatRect inter = intersectionOpt.value();
        sf::FloatRect eBounds = getBounds();

        if (inter.size.x < inter.size.y) {
            if (inter.size.x > 2.0f) {
                if (vecspeed.x > 0) {
                    sprite.setPosition({ pBounds.position.x - eBounds.size.x - 0.1f, sprite.getPosition().y });
                }
                else {
                    sprite.setPosition({ pBounds.position.x + pBounds.size.x + 0.1f, sprite.getPosition().y });
                }
                bounce();
            }
        }
        else {
            if (vecspeed.y >= 0 && eBounds.position.y < pBounds.position.y) {
                sprite.setPosition({ sprite.getPosition().x, pBounds.position.y - eBounds.size.y });
                vecspeed.y = 0.f;

                onGround = true;                 
                currentPlatformBounds = pBounds; 
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
    if (type == EnemyType::Goomba) {
        squashed = true;
        vecspeed = { 0.f, 0.f };
        float oldHeight = getBounds().size.y;
        sprite.setTextureRect(sf::IntRect({ 57, 16 }, { 18, 6 }));
        float newHeight = getBounds().size.y;
        sprite.move({ 0.f, oldHeight - newHeight });
    }
    else if (type == EnemyType::Troopa) {
        squashed = true;
        shellMoving = false;
        vecspeed = { 0.f, 0.f };
        float oldHeight = getBounds().size.y;
        sprite.setTextureRect(sf::IntRect({ 36, 9 }, { 16, 14 }));
        float newHeight = getBounds().size.y;
        sprite.move({ 0.f, oldHeight - newHeight });
    }
}

bool Enemy::isSquashed() const { return squashed; }
EnemyType Enemy::getType() const { return type; }
bool Enemy::isShellMoving() const { return shellMoving; }

void Enemy::kick(float marioX) {
    shellMoving = true;

    if (marioX < sprite.getPosition().x) {
        vecspeed = { 300.f, 0.f };
        sprite.move({ 5.f, 0.f });
    }
    else {
        vecspeed = { -300.f, 0.f };
        sprite.move({ -5.f, 0.f });
    }
}

void Enemy::knockOut() {
    if (knockedOut) return;
    knockedOut = true;
    vecspeed.y = -100.f;
    sprite.setScale({ 2.5f, -2.5f });
    sprite.move({ 0.f, sprite.getGlobalBounds().size.y });
}

bool Enemy::isKnockedOut() const { return knockedOut; }