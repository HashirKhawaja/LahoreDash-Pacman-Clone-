
#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
public:
    Enemy(const char* imagePath, float startX, float startY);

    void handlemovement(const sf::FloatRect& playerBounds);

    bool checkCollision(const sf::FloatRect& playerBounds) const;

    void draw(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite shape;
    sf::Image CollisionImage;

    bool isPathPixel(int x, int y) const;
    bool isWalkable(int x, int y) const;
};
