#pragma once
#include <SFML/Graphics.hpp>

class HUD {
public:
    HUD();
    void init(const sf::Font& font);
    void update();
    //void setPosition(float x, float y);
    void draw(sf::RenderWindow& window) const;

    void addScore(int amount);
    void setScore(int s);
    int getScore() const;
    void reset();

    void setCoins(int count, int points);

	sf::Texture coinTexture;

private:
    void updateScoreText();
    void updateCoinText();
    void updateTimeText();

    std::unique_ptr<sf::Text> scoreText;
    std::unique_ptr<sf::Text> coinText;
    std::unique_ptr<sf::Text> timeText;
    sf::RectangleShape background;
    sf::CircleShape coinIcon;


    int score = 0;
    int coins = 0;
    int coinPoints = 0;
    int timeLeft = 400;

    int lastScore = -1;
    int lastCoins = -1;
    int lastCoinPoints = -1;
    int lastTime = -1;

    sf::Clock timerClock;
};
