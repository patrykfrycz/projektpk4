#include "SuperMushroom.h"
#include "Player.h"

SuperMushroom::SuperMushroom(float x, float y) : Item(ItemType::Mushroom, x, y, 32.f, 32.f) {
    vecspeed = { 150.f, -200.f };
}

void SuperMushroom::initTexture(const sf::Texture& texture) {
    sprite.emplace(texture);
    sprite->setPosition(initialPosition);
    sprite->setScale({ 2.5f, 2.5f });
}

void SuperMushroom::update() {
    float dt = 1.0f / 60.0f;
    vecspeed.y += gravity * dt;

    if (sprite.has_value()) {
        sprite->move(vecspeed * dt);
        shape.setPosition(sprite->getPosition());
    }
}

void SuperMushroom::draw(sf::RenderWindow& window) const {
    if (!active) return;
    if (sprite.has_value() && active) {
        window.draw(*sprite);
    }
}

sf::FloatRect SuperMushroom::getBounds() const {
    if (sprite.has_value()) {
        return sprite->getGlobalBounds();
    }
    return shape.getGlobalBounds();
}

void SuperMushroom::resolveCollision(const Platform& platform) {
    if (!sprite.has_value() || !active) return;

    auto interOpt = sprite->getGlobalBounds().findIntersection(platform.getBounds());
    if (interOpt.has_value()) {
        sf::FloatRect inter = interOpt.value();
        sf::FloatRect sB = sprite->getGlobalBounds();
        sf::FloatRect pB = platform.getBounds();

        if (inter.size.x < inter.size.y) {
            vecspeed.x = -vecspeed.x;
        }
        else {
            if (sB.position.y < pB.position.y) {
                sprite->setPosition({ sB.position.x, pB.position.y - sB.size.y });
                vecspeed.y = 0.f;
            }
        }
    }
}

void SuperMushroom::onPickup(Player& player) {

    Item::onPickup(player);
    player.activateGrow();
}