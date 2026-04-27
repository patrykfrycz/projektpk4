#include "Item.h"
#include <cmath>
#include "Coin.h"

Item::Item(ItemType t, float x, float y, float width, float height)
    : type(t), initialPosition{ x, y }, active(true)
{
    shape.setSize({ width, height });
    shape.setPosition(initialPosition);
    shape.setOutlineThickness(0.f);
	shape.setFillColor(sf::Color::White);

    // proste kolory zale¿ne od typu (mo¿esz zamieniæ na tekstury)
    switch (type) {
    case ItemType::Coin:     shape.setFillColor(sf::Color::Yellow); break;
    case ItemType::Mushroom: shape.setFillColor(sf::Color(200, 50, 50)); break;
    case ItemType::Flower:   shape.setFillColor(sf::Color::Magenta); break;
    case ItemType::Star:     shape.setFillColor(sf::Color::Cyan); break;
    }
}

void Item::update() {
    // domyœlnie brak animacji - mo¿liwoœæ dodania jej pozniej
}

void Item::draw(sf::RenderWindow& window) const {
    if (!active) return;
    window.draw(shape);
}

sf::FloatRect Item::getBounds() const {
    return shape.getGlobalBounds();
}

bool Item::isActive() const {
    return active;
}

ItemType Item::getType() const {
    return type;
}

void Item::setOnPickup(std::function<void(Player&)> cb) {
    pickupCallback = std::move(cb);
}

void Item::onPickup(Player& player) {
    if (pickupCallback) pickupCallback(player);
    active = false;
}

void Item::setPosition(float x, float y) {
    initialPosition = { x, y };
    shape.setPosition(initialPosition);
}

void Item::reset() {
    active = true;
    shape.setPosition(initialPosition);
}
