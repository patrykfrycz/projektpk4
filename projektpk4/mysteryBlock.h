#pragma once
#include "Platform.h" 
#include <functional>

class MysteryBlock : public Platform {
private:
    const sf::Texture* activeTexture = nullptr;
    const sf::Texture* emptyTexture = nullptr;

    bool isUsed = false;
    bool isBouncing = false;
    float bounceVelocity = 0.f;

    std::function<void(sf::Vector2f)> onHitCallback;

public:
    MysteryBlock(float x, float y, float width, float height);

    void initTextures(const sf::Texture& activeTex, const sf::Texture& usedTex);

    void setOnHitCallback(std::function<void(sf::Vector2f)> callback);

    void update(float deltaTime);

    void resolveCollision(Player& player);

    void resetBlock();
};