#include "Player.h"

Player::Player() {
	speed = 5.f;
	gravity = 0.5f;
	speedY = 0.f;
	jumpPower = 15.f;
	canJump = false;
}

void Player::initTexture(const sf::Texture& texture) {
	sprite.emplace(texture);

	standFrame = sf::IntRect({ 14, 27 }, { 19, 32 });

	walkFrames.push_back(sf::IntRect({ 66, 27 }, { 19, 32 }));
	walkFrames.push_back(sf::IntRect({ 116, 27 }, { 19, 32 }));

	jumpFrame = sf::IntRect({ 262, 27 }, { 19, 32 });

	sprite->setTextureRect(standFrame);

	sprite->setOrigin({ 9.5f, 0.f });

	sprite->setScale({ 2.f, 2.f });
	sprite->setPosition({ 100.f, 100.f });
}

void Player::update() {
	bool isMoving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
		sprite->move({ -speed, 0.f });
		sprite->setScale({ -2.f, 2.f });
		isMoving = true;
	}

	// RUCH W PRAWO
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		sprite->move({ speed, 0.f });
		sprite->setScale({ 2.f, 2.f });
		isMoving = true;
	}

	if (!canJump) {

		sprite->setTextureRect(jumpFrame);
	}
	else if (isMoving) {
		if (animClock.getElapsedTime().asSeconds() > 0.1f) {
			animFrame++;

			if (animFrame >= walkFrames.size()) {
				animFrame = 0;
			}

			sprite->setTextureRect(walkFrames[animFrame]);
			animClock.restart();
		}
	}
	else {
		animFrame = 0;
		sprite->setTextureRect(standFrame);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && canJump) {
		speedY = -jumpPower;
		canJump = false;
	}

	speedY += gravity;

	sprite->move({ 0.f, speedY });
}

void Player::draw(sf::RenderWindow& window)
{
	if (sprite.has_value()) {
		window.draw(*sprite);
	}
}

sf::FloatRect Player::getBounds() const {
	return sprite->getGlobalBounds();
}

void Player::stopFalling(float platformTopY) {
	sprite->setPosition({ sprite->getPosition().x, platformTopY - sprite->getGlobalBounds().size.y });

	speedY = 0.f; // Zatrzymujemy pêd w dó³
	canJump = true;  // Jesteœmy na ziemi, mo¿emy znowu skakaæ
}

void Player::reset() {
	sprite->setPosition({ 100.f, 300.f });
	speedY = 0.f;
	canJump = false;
}

float Player::getX() const {
	return sprite->getPosition().x;
}

float Player::getY() const {
	return sprite->getPosition().y;
}

void Player::setX(float x) {
	sprite->setPosition({ x, sprite->getPosition().y });
}

void Player::setY(float y) {
	sprite->setPosition({ sprite->getPosition().x, y });
	speedY = 0.f;
}

void Player::bounceUp() {
	speedY = -jumpPower * 0.7f;
	canJump = false;
}