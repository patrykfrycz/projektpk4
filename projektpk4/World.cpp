#include "World.h"
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <optional>
#include <iostream>

World::World(const sf::Vector2u& windowSize)
    : player({ 64.f, 64.f }, { 100.f, 100.f }), backgroundTex("tlo.png"),
    backgroundSprite(backgroundTex)
{
    // Wczytanie t³a
    if (!backgroundTex.loadFromFile("tlo.png")) {
        std::cerr << "Nie mo¿na za³adowaæ pliku tlo.png!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTex);
    backgroundSprite.setScale(sf::Vector2f(
        2.f * static_cast<float>(windowSize.x) / backgroundTex.getSize().x,
        static_cast<float>(windowSize.y) / backgroundTex.getSize().y
    ));

    // Dodanie przyk³adowej platformy
    // addPlatform({ 0.f, 550.f }, { 800.f, 50.f }, sf::Color(100, 100, 100));
}

void World::update(float dt) {

    std::vector<sf::FloatRect> platformRects;
    for (const auto& platform : platforms) {
        platformRects.push_back(platform.getBounds());
    }

    // Aktualizacja gracza
    player.update(dt, platformRects);
}

void World::render(sf::RenderWindow& window) {

    window.draw(backgroundSprite);

    for (const auto& platform : platforms) {
        platform.draw(window);
    }

    player.draw(window);
}

Player& World::getPlayer() {
    return player;
}

void World::addPlatform(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color) {
    platforms.emplace_back(position, size, color);
}