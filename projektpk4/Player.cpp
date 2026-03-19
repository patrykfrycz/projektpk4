#include "Player.h"

Player::Player() {
	shape.setSize({ 50.f, 50.f });
	shape.setFillColor(sf::Color::Red);
	shape.setPosition({100.f, 100.f});

	speed = 5.f;
	gravity = 3.f;
}

void Player::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		shape.move({ -speed, 0.f });
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		shape.move({ speed, 0.f });
	}

	shape.move({ 0.f, gravity });
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

