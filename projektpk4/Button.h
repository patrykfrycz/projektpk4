#pragma once
#include <SFML/Graphics.hpp>

class Button {
private:
	sf::RectangleShape shape;
	//sf::Text text;

public:
	Button();
	void draw(sf::RenderWindow& window);
	bool isClicked(sf::RenderWindow& window);
};