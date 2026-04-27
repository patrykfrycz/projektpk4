#include "Coin.h"
#include "Item.h"
#include "HUD.h"
#include "Game.h"

int Coin::collectedCount = 0;
int Coin::collectedPoints = 0;

Coin::Coin(float x, float y, float size)
    : Item(ItemType::Coin, x, y, size, size), bobPhase(0.f), value(value)
{
    if (!texture.loadFromFile("coin.png")) {
        shape.setFillColor(sf::Color::Yellow);
    }
    else {
        shape.setTexture(&texture);
    }

    //shape.setFillColor(sf::Color::Yellow);
    //shape.setOutlineColor(sf::Color::Yellow);
    shape.setOutlineThickness(0.f);


}

void Coin::update() {
    bobPhase += 0.12f;
    float dy = std::sin(bobPhase) * 6.f;
    //shape.setPosition(initialPosition.x, initialPosition.y + dy); //- bujanie w update - do dokonczenia
}

void Coin::onPickup(Player& player) {
    Item::onPickup(player);

    ++collectedCount;
    collectedPoints += value;
}

int Coin::getCollectedCount() { return collectedCount; }
int Coin::getCollectedPoints() { return collectedPoints; }


void Coin::resetCounters() {
    collectedCount = 0;
    collectedPoints = 0;
}

void Coin::coinCollect(HUD& hud, std::vector<std::unique_ptr<Item>>& items, sf::Vector2f position) {

    items.emplace_back(std::make_unique<Coin>(position.x, position.y));
    items.back()->setOnPickup([&hud](Player& p) {
        hud.addScore(10);
        });
}

