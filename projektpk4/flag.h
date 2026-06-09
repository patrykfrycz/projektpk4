#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <concepts> // <--- DODAJEMY BIBLIOTEKÊ KONCEPTÓW

// =========================================================================
// DEFINIUJEMY KONCEPT:
// "T jest zderzalne (Collidable), jeœli posiada funkcjê getBounds(), 
// która po wywo³aniu zwraca coœ, co da siê zamieniæ na sf::FloatRect"
// =========================================================================
template <typename T>
concept Collidable = requires(const T & obj) {
    { obj.getBounds() } -> std::convertible_to<sf::FloatRect>;
};


class Flag {
private:
    std::optional<sf::Sprite> sprite;
    sf::Vector2f position;

public:
    Flag(float x, float y);

    void initTexture(const sf::Texture& texture);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    template <Collidable T>
    bool checkCollision(const T& object) const {
        return object.getBounds().findIntersection(getBounds()).has_value();
    }
};