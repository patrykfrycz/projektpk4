#include "MysteryBlock.h"

MysteryBlock::MysteryBlock(float x, float y, float width, float height)
    : Platform(x, y, width, height) {
}

void MysteryBlock::initTextures(const sf::Texture& activeTex, const sf::Texture& usedTex) {
    activeTexture = &activeTex;
    emptyTexture = &usedTex;

    sprite.emplace(*activeTexture);
    sprite->setTextureRect(sf::IntRect({ 0, 0 }, { (int)size.x, (int)size.y }));
    sprite->setPosition(initialPosition);
}

void MysteryBlock::update(float deltaTime) {
    if (isBouncing) {
        sprite->move({ 0.f, bounceVelocity * deltaTime });
        bounceVelocity += 1500.f * deltaTime;

        if (sprite->getPosition().y >= initialPosition.y) {
            sprite->setPosition(initialPosition);
            isBouncing = false;
        }
    }
}

void MysteryBlock::resetBlock() {
    isUsed = false;
    isBouncing = false;
    bounceVelocity = 0.f;
    if (sprite.has_value() && activeTexture) {
        sprite->setPosition(initialPosition);
        sprite->setTexture(*activeTexture);
    }
}

void MysteryBlock::setOnHitCallback(std::function<void(sf::Vector2f)> callback) {
    onHitCallback = callback;
}

void MysteryBlock::resolveCollision(Player& player) {
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

            if (!isUsed) {
                isUsed = true;
                isBouncing = true;
                bounceVelocity = -300.f;

                if (emptyTexture && sprite.has_value()) {
                    sprite->setTexture(*emptyTexture);
                }

  
                if (onHitCallback) {
                    onHitCallback({ initialPosition.x, initialPosition.y - 32.f });
                }

            }
        }
    }
}