#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
	sf::RectangleShape shape;
	sf::Text text;

public:
	Button(float x, float y, float tx, float ty, const sf::Font& font, std::string buttonText);
	void draw(sf::RenderWindow& window);
	bool isClicked(sf::RenderWindow& window);
	//void updateText(std::string newText);
};