#include "Player.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

Player::Player(const sf::Vector2f& size, const sf::Vector2f& startPos) {
	shape.setSize({64.f, 64.f});
	shape.setFillColor(sf::Color::Red);
	shape.setPosition({600, 600});

	speed = 5.f;
	gravity;
    bool StaysOnGround = false;
}

void Player::update(float dt, const std::vector<sf::FloatRect>&platforms) {
    bool StaysOnGround = false;
	float jumpStrength = 20.f;
	// grawitacja
	//velocity.y += gravity;
	//shape.move(velocity * dt);

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
	//	shape.move({ -speed, 0.f });
	//}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
	//	shape.move({ speed, 0.f });
	//}

	//shape.move({ 0.f, gravity });



    if (dt <= 0.f) return;

    // horizontal movement (pixels per second)
    float moveX = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        shape.move({ -speed, 0.f });
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
	    shape.move({ speed, 0.f });
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && StaysOnGround) { // do dopisania ¿e jeœli jest na platformie to mo¿e skakaæ
        velocity.y = -jumpStrength;
		StaysOnGround = false;
    }

    velocity.y += gravity * dt;

    // zapamiêtaj star¹ pozycjê
    //float prevY = y;

//    // --- RUCH ---
//    x += velocityX;
//    y += velocityY;
//
//    // --- KOLIZJA Z PLATFORM¥ ---
//    if (checkCollision(getRect(), platform)) {
//        // sprawdzamy czy spada³ z góry
//        if (prevY + height <= platform.y) {
//            y = platform.y - height;
//            velocityY = 0;
//            isOnGround = true;
//        }
//    }
}

void Player::draw(sf::RenderWindow& window) const
{
	window.draw(shape);
}

