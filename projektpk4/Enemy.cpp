#include "Enemy.h"

Enemy::Enemy(sf::Texture& texture, sf::Vector2f startPos) : sprite(texture) {
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 18, 22 }));
    sprite.setPosition(startPos);

    walkSpeed = -50.f; // Zaczyna id¹c w lewo
    vecspeed.x = walkSpeed;
}

void Enemy::update(float deltaTime) {
    // Prosty ruch: mno¿ymy prêdkoœæ przez czas klatki
    sprite.move(vecspeed * deltaTime);
}

void Enemy::bounce() {
    // Odwracamy kierunek ruchu
    vecspeed.x = -vecspeed.x;
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}