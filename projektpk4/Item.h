#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Player;

enum class ItemType { Coin, Mushroom, Flower, Star };

class Item {
protected:
    Item(ItemType type, float x, float y, float width = 32.f, float height = 32.f);

public: 
    virtual ~Item() = default;

    virtual void update();
    virtual void draw(sf::RenderWindow& window) const; 

    virtual sf::FloatRect getBounds() const;
    bool isActive() const;
    ItemType getType() const;

    void setOnPickup(std::function<void(Player&)> cb);
    virtual void onPickup(Player& player);

    void setPosition(float x, float y);
    void reset();

protected: 
    ItemType type;
    sf::RectangleShape shape;
    sf::Vector2f initialPosition;
    bool active = true;
    std::function<void(Player&)> pickupCallback;
};