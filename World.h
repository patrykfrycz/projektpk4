#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Player.h"

class World {
private:
    sf::Texture backgroundTex; // T³o œwiata
    sf::Sprite backgroundSprite; // Sprite t³a
    std::vector<Platform> platforms; // Lista platform
    Player player; // Gracz

public:
    // Konstruktor - inicjalizuje œwiat
    World(const sf::Vector2u& windowSize);

    // Metoda aktualizuj¹ca œwiat (fizyka, kolizje, itp.)
    void update(float dt);

    // Metoda rysuj¹ca œwiat
    void render(sf::RenderWindow& window);

    // Pobiera referencjê do gracza
    Player& getPlayer();

    // Dodaje platformê do œwiata
    void addPlatform(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::Yellow);
};