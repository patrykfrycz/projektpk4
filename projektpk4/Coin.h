#pragma once
#include "Item.h"
#include <cmath>
#include "HUD.h"

class Coin : public Item {
public:
    Coin(float x, float y, float size = 24.f);
    void update() override;
    void onPickup(Player& player) override;

    static int getCollectedCount();
    static int getCollectedPoints();
    static void resetCounters();
	void coinCollect(HUD& hud, std::vector<std::unique_ptr<Item>>& items, sf::Vector2f position);

private:
    float bobPhase = 0.f;
    int value = 10;
    static int collectedCount;
    static int collectedPoints;
};
