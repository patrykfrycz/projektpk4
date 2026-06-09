#include "Star.h"

Star::Star(float x, float y) : Item(ItemType::Star, x, y, 32.f, 32.f) {
    vecspeed = { 150.f, -400.f };

}

void Star::initTexture(const sf::Texture& texture) {
    sprite.emplace(texture);
    sprite->setPosition(initialPosition); 
    sprite->setScale({ 2.5f, 2.5f });
}

void Star::update() {
    float dt = 1.0f / 60.0f;
    vecspeed.y += 800.f * dt;

    if (sprite.has_value()) {
        sprite->move(vecspeed * dt);
        shape.setPosition(sprite->getPosition());
    }
}

void Star::draw(sf::RenderWindow& window) const {
    if (sprite.has_value() && active) { 
        window.draw(*sprite);
    }
}

sf::FloatRect Star::getBounds() const {
    if (sprite.has_value()) {
        return sprite->getGlobalBounds();
    }
    return shape.getGlobalBounds();
}

void Star::resolveCollision(const Platform& platform) {
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
                vecspeed.y = -350.f;
            }
        }
    }
}