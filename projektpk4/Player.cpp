#include "Player.h"

Player::Player() {
	shape.setSize({ 50.f, 50.f });
	shape.setFillColor(sf::Color::Red);
	shape.setPosition({ 100.f, 100.f });

	speed = 5.f;

	gravity = 0.5f;
	speedY = 0.f;
	jumpPower = 12.f;
	canJump = false;
}

void Player::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		shape.move({ -speed, 0.f });
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		shape.move({ speed, 0.f });
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && canJump) {
		speedY = -jumpPower;
		canJump = false;
	}

	speedY += gravity;

	shape.move({ 0.f, speedY });
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}


sf::FloatRect Player::getBounds() const {
	return shape.getGlobalBounds();
}

void Player::stopFalling(float platformTopY) {
	shape.setPosition({ shape.getPosition().x, platformTopY - shape.getSize().y });

	speedY = 0.f; // Zatrzymujemy pêd w dó³
	canJump = true;  // Jesteœmy na ziemi, mo¿emy znowu skakaæ
}


void Player::reset() {
	shape.setPosition({ 100.f, 300.f });
	speedY = 0.f;
	canJump = false;
}

float Player::getX() const {
	return shape.getPosition().x;
}

float Player::getY() const{
	return shape.getPosition().y;
}

void Player::setX(float x) {
	shape.setPosition({ x, shape.getPosition().y });
}