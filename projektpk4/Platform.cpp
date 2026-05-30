#include "Platform.h"
#include "Player.h"

Platform::Platform(float x, float y, float width, float height) : initialPosition{ x, y }, size{ width, height } {
    // Konstruktor tylko zapamiêtuje wymiary i pozycjê na póŸniej
}

void Platform::initTexture(const sf::Texture& texture) {
    sprite.emplace(texture);

    sprite->setTextureRect(sf::IntRect({ 0, 0 }, { (int)size.x, (int)size.y }));

    sprite->setPosition(initialPosition);
}

void Platform::draw(sf::RenderWindow& window) {
    if (sprite.has_value()) {
        window.draw(*sprite);
    }
}

sf::FloatRect Platform::getBounds() const {
    if (sprite.has_value()) {
        return sprite->getGlobalBounds();
    }
    return sf::FloatRect(initialPosition, size);
}

void Platform::resetPlatform() {
    if (sprite.has_value()) {
        sprite->setPosition(initialPosition);
    }
}

void Platform::resolveCollision(Player& player) const {
    auto interOpt = player.getBounds().findIntersection(getBounds());
    if (!interOpt.has_value()) return;

    sf::FloatRect inter = interOpt.value();
    sf::FloatRect pB = player.getBounds();
    sf::FloatRect plB = getBounds();

    if (inter.size.x < inter.size.y) {
        float pCenterX = pB.position.x + pB.size.x * 0.5f;
        float plCenterX = plB.position.x + plB.size.x * 0.5f;
        if (pCenterX < plCenterX) {
            player.setX(plB.position.x - pB.size.x - 0.1f);
        }
        else {
            player.setX(plB.position.x + plB.size.x + 0.1f);
        }
    }
    else {
        float pCenterY = pB.position.y + pB.size.y * 0.5f;
        float plCenterY = plB.position.y + plB.size.y * 0.5f;
        if (pCenterY < plCenterY) {
            player.stopFalling(plB.position.y);
        }
        else {
            player.setY(plB.position.y + plB.size.y + 0.1f);
        }
    }
}