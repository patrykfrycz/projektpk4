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

    if (jumpBuffer.loadFromFile("skok.wav")) {
        jumpSound.emplace(jumpBuffer);
    }
}

void Player::update() {

    if (invincibleTimer > 0.f) {
        invincibleTimer -= 1.0f / 60.0f;
    }

    if (starMode) {
        starTimer -= 1.0f / 60.0f;
        if (starTimer <= 0.f) {
            starMode = false; 
        }
    }

    if (dead) {
        speedY += gravity;
        sprite->move({ 0.f, speedY });
        return; 
    }

    bool isMoving = false;
    float scaleMag = miniMode ? 1.5f : 2.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        sprite->move({ -speed, 0.f });
        sprite->setScale({ -scaleMag, scaleMag });
        isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        sprite->move({ speed, 0.f });
        sprite->setScale({ scaleMag, scaleMag });
        isMoving = true;
    }

    sf::IntRect currentFrame;

    if (!canJump) {
        currentFrame = jumpFrame;
    }
    else if (isMoving) {
        if (animClock.getElapsedTime().asSeconds() > 0.1f) {
            animFrame++;
            if (animFrame >= walkFrames.size()) {
                animFrame = 0;
            }
            animClock.restart();
        }
        currentFrame = walkFrames[animFrame];
    }
    else {
        animFrame = 0;
        currentFrame = standFrame;
    }

    if (starMode) {
        currentFrame.position.y += 235;
    }

    sprite->setTextureRect(currentFrame);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && canJump) {
        speedY = -jumpPower;
        canJump = false;

        if (jumpSound.has_value()) {
            jumpSound->play();
        }
    }

    speedY += gravity;
    sprite->move({ 0.f, speedY });
}

void Player::draw(sf::RenderWindow& window) {
    if (sprite.has_value()) {
        if (invincibleTimer > 0.f) {
            if (static_cast<int>(invincibleTimer * 10) % 2 == 0) {
                sprite->setColor(sf::Color(255, 255, 255, 100));
            }
            else {
                sprite->setColor(sf::Color::White); 
            }
        }
        else {
            sprite->setColor(sf::Color::White); 
        }

        window.draw(*sprite);
    }
}

sf::FloatRect Player::getBounds() const {
	return sprite->getGlobalBounds();
}

void Player::stopFalling(float platformTopY) {
	sprite->setPosition({ sprite->getPosition().x, platformTopY - sprite->getGlobalBounds().size.y });

	speedY = 0.f; 
	canJump = true;  
}

void Player::reset() {
	sprite->setPosition({ 100.f, 300.f });
	speedY = 0.f;
	canJump = false;
    dead = false;
    miniMode = false;
    speed = 5.f;
    invincibleTimer = 0.f;
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

void Player::activateStar() {
	starMode = true;
	starTimer = 10.f; 
}

bool Player::hasStar() const {
	return starMode;
}

void Player::die() {
    dead = true;
    speedY = -12.f; 
    starMode = false;
}

bool Player::isDead() const {
    return dead;
}

void Player::activateMini() {
    miniMode = true;
    speed = 10.f; 
}

void Player::deactivateMini() {
    miniMode = false;
    speed = 5.f; 

    sprite->move({ 0.f, -32.f });
    invincibleTimer = 2.0f;
}

bool Player::isInvincible() const {
    return invincibleTimer > 0.f;
}

bool Player::isMini() const {
    return miniMode;
}

void Player::activateGrow() {
    if (!sprite.has_value()) return;
    if (isBig()) return;

    sf::FloatRect before = getBounds();
    float bottomY = before.position.y + before.size.y;

    sf::Vector2f s = sprite->getScale();
    sprite->setScale({ s.x * 2.f, s.y * 2.f });

    sf::FloatRect after = getBounds();
    float newY = bottomY - after.size.y;
    sprite->setPosition({ sprite->getPosition().x, newY });

    bigMode = true;
}

void Player::deactivateGrow() {
    if (!sprite.has_value()) return;
    if (!isBig()) return;

    sf::FloatRect before = getBounds();
    float bottomY = before.position.y + before.size.y;

    sf::Vector2f s = sprite->getScale();
    sprite->setScale({ s.x * 0.5f, s.y * 0.5f });

    sf::FloatRect after = getBounds();
    float newY = bottomY - after.size.y;
    sprite->setPosition({ sprite->getPosition().x, newY });

    bigMode = false;
}

bool Player::isBig() const {
    return bigMode;
}