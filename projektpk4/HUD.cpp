#include "HUD.h"
#include "Coin.h" // u¿ywane w update() do pobrania liczby zebranych coinów
#include <string>
#include <memory>

HUD::HUD()
    : score(0), coins(0), coinPoints(0),
    lastScore(-1), lastCoins(-1), lastCoinPoints(-1)
{
}

void HUD::init(const sf::Font& font) {
    // create texts with font (SFML3 requires font in ctor)
    scoreText = std::make_unique<sf::Text>(font, "Score\n0", 26u);
    scoreText->setFillColor(sf::Color::White);
    scoreText->setOutlineThickness(2.f);
    scoreText->setOutlineColor(sf::Color::Black);
    scoreText->setPosition({ 280.f, 14.f });

    coinText = std::make_unique<sf::Text>(font, "Coins: 0 (0)", 26u);
    coinText->setFillColor(sf::Color::Yellow);
    coinText->setOutlineThickness(2.f);
    coinText->setOutlineColor(sf::Color::Black);
    coinText->setPosition({ 440.f, 14.f });

    timeText = std::make_unique<sf::Text>(font, "Time: 400", 26u);
    timeText->setFillColor(sf::Color::White);
    timeText->setOutlineThickness(2.f);
    timeText->setOutlineColor(sf::Color::Black);
    timeText->setPosition({ 570.f, 14.f });

    const float iconRadius = 10.f;
    coinIcon.setRadius(iconRadius);
    coinIcon.setFillColor(sf::Color::Yellow);
    coinIcon.setOutlineColor(sf::Color(150, 120, 0));
    coinIcon.setOutlineThickness(1.f);

    background.setSize({ 220.f, 80.f });
    background.setFillColor(sf::Color(0, 0, 0, 150));
    //background.setPosition({ 8.f, 8.f });

    reset();
}

void HUD::update() {
    //odczytujemy statystyki coinów i aktualizujemy teksty
    setCoins(Coin::getCollectedCount(), Coin::getCollectedPoints());
    updateScoreText();
    //updateCoinText();

    if (timerClock.getElapsedTime().asSeconds() >= 1.0f) {
        if (timeLeft > 0) {
            timeLeft--;
        }
        timerClock.restart();
    }
    updateTimeText();
}

void HUD::draw(sf::RenderWindow& window) const {
    //window.draw(background);
    //window.draw(coinIcon);

    if (scoreText) window.draw(*scoreText);
    if (coinText)  window.draw(*coinText);
    if (timeText)  window.draw(*timeText);
}

void HUD::addScore(int amount) {
    score += amount;
    updateScoreText();
}

void HUD::setScore(int s) {
    score = s;
    updateScoreText();
}

int HUD::getScore() const {
    return score;
}

void HUD::setCoins(int coin, int points) {
    coins = coin;
    updateCoinText();
}

void HUD::updateScoreText() {
    if (!scoreText) return;
    if (score != lastScore) {
        // Dodajemy \n, ¿eby liczba by³a pod spodem
        scoreText->setString("SCORE\n" + std::to_string(score));
        lastScore = score;
    }
}

void HUD::updateCoinText() {
    if (!coinText) return;
    if (coins != lastCoins) {
        // Dodajemy \n, ¿eby liczba by³a pod spodem
        coinText->setString("COINS\n" + std::to_string(coins));
        lastCoins = coins;
    }
}

void HUD::updateTimeText() {
    if (!timeText) return;
    if (timeLeft != lastTime) {
        // Dodajemy \n, ¿eby liczba by³a pod spodem
        timeText->setString("TIME\n" + std::to_string(timeLeft));
        lastTime = timeLeft;
    }
}

void HUD::reset() {
    score = 0;
    coins = 0;
    //coinPoints = 0;
    timeLeft = 400;

    lastScore = -1;
    lastCoins = -1;
    //lastCoinPoints = -1;
    lastTime = -1;

    //updateScoreText();
	//updateCoinText();
    timerClock.restart();
}