#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Platform {
private:
	sf::RectangleShape shape;
	sf::Vector2f initialPosition;
public:
	Platform(float x, float y, float width, float height);

	void draw(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

	void resetPlatform();

	void resolveCollision(Player& player) const;
};
