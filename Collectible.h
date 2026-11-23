
#pragma once

#include <SFML/Graphics.hpp>

class Points;

class Collectible
{
public:
    Collectible();

    bool allCollected() const;
    void checkCollision(const sf::FloatRect& playerBounds, Points& points);
    void draw(sf::RenderWindow& window) const;

private:
    static const int MAX_COLLECTIBLES = 32;

    struct Item
    {
        sf::Vector2f position;
        int textureIndex;
        int pointValue;
        bool collected;
    };

    sf::Texture textures[4];
    sf::Image collisionMap;

    Item items[MAX_COLLECTIBLES];
    int itemCount = 0;

    void placeCollectibles();
    bool isPathPixel(int x, int y) const;
    bool isWalkable(int x, int y) const;
};
