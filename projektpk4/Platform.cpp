#include "Platform.h"
#include "Player.h"

Platform::Platform(float x, float y, float width, float height) : initialPosition{x, y} {
    shape.setPosition({ x, y });
    shape.setSize({ width, height });
    shape.setFillColor(sf::Color::Green);
}

void Platform::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Platform::getBounds() const {
    return shape.getGlobalBounds();
}

void Platform::resetPlatform() {
    shape.setPosition(initialPosition);
}

/*void Platform::createPlatform(Platform platform, Player mario) {
    //shape = platform.shape;
    //initialPosition = platform.initialPosition;

    std::optional<sf::FloatRect> intersection = mario.getBounds().findIntersection(platform.getBounds());

    if (intersection.has_value()) {
        sf::FloatRect playerBounds = mario.getBounds();
        sf::FloatRect platBounds = platform.getBounds();
        sf::FloatRect inter = intersection.value();

        // wybierz mniejsz¹ penetracjê: pozioma -> blokada X, pionowa -> blokada Y
        if (inter.size.x < inter.size.y) {
            // kolizja pozioma — wypchnij po osi X
            float playerCenterX = playerBounds.position.x + playerBounds.size.x * 0.5f;
            float platCenterX = platBounds.position.x + platBounds.size.x * 0.5f;
            if (playerCenterX < platCenterX) {
                // gracz z lewej strony platformy -> ustaw x tak, ¿eby sta³ tu¿ obok
                mario.setX(platBounds.position.x - playerBounds.size.x - 0.1f);
            }
            else {
                // gracz z prawej strony -> ustaw x na prawo od platformy
                mario.setX(platBounds.position.x + platBounds.size.x + 0.1f);
            }
        }
        else {
            // kolizja pionowa
            float playerCenterY = playerBounds.position.y + playerBounds.size.y * 0.5f;
            float platCenterY = platBounds.position.y + platBounds.size.y * 0.5f;
            if (playerCenterY < platCenterY) {
                // gracz nad platform¹ -> l¹duje na wierzchu
                mario.stopFalling(platBounds.position.y);
            }
            else {
                // gracz pod platform¹ -> "uderzenie g³ow¹" -> wypchnij ni¿ej i zeruj prêdkoœæ pionow¹
                mario.setY(platBounds.position.y + platBounds.size.y + 0.1f);
            }
        }
    }
}*/

void Platform::resolveCollision(Player& player) const {
    auto interOpt = player.getBounds().findIntersection(getBounds());
    if (!interOpt.has_value()) return;

    sf::FloatRect inter = interOpt.value();
    sf::FloatRect pB = player.getBounds();
    sf::FloatRect plB = getBounds();

    // choose smaller penetration: horizontal or vertical
    if (inter.size.x < inter.size.y) {
        // horizontal push
        float pCenterX = pB.position.x + pB.size.x * 0.5f;
        float plCenterX = plB.position.x + plB.size.x * 0.5f;
        if (pCenterX < plCenterX) {
            // player is to the left -> push left
            player.setX(plB.position.x - pB.size.x - 0.1f);
        }
        else {
            // player to the right -> push right
            player.setX(plB.position.x + plB.size.x + 0.1f);
        }
    }
    else {
        // vertical push
        float pCenterY = pB.position.y + pB.size.y * 0.5f;
        float plCenterY = plB.position.y + plB.size.y * 0.5f;
        if (pCenterY < plCenterY) {
            // player above -> land on top
            player.stopFalling(plB.position.y);
        }
        else {
            // player below -> push down and stop vertical speed
            player.setY(plB.position.y + plB.size.y + 0.1f);
        }
    }
}