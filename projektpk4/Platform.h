#pragma once
#include <SFML/Graphics.hpp>

class Platform {
private:
	sf::RectangleShape shape;
public:
	Platform(float x, float y, float width, float height);

	void draw(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

	void resetPlatform();
};
