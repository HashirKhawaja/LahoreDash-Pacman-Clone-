#include "Collectible.h"
#include "Points.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Collectible::Collectible()
    : collisionMap("assets/CollisionMap.png")
{
    const char* assetPaths[4] =
    {
        "assets/jalebi.png",
        "assets/samosa.png",
        "assets/kulfi.png",
        "assets/lassi.png"
    };

    for (int i = 0; i < 4; i++)
    {
        if (!textures[i].loadFromFile(assetPaths[i]))
        {
            std::cout << "Could not load: "
                << assetPaths[i] << std::endl;
        }
    }

    std::srand(std::time(nullptr));

    placeCollectibles();
}


// Check whether a pixel is a path.
bool Collectible::isPathPixel(int x, int y) const
{
    if (x < 0 || y < 0)
        return false;

    sf::Vector2u pixelPosition;

    pixelPosition.x = x;
    pixelPosition.y = y;

    sf::Vector2u mapSize = collisionMap.getSize();

    if (pixelPosition.x >= mapSize.x ||
        pixelPosition.y >= mapSize.y)
        return false;

    if (collisionMap.getPixel(pixelPosition) == sf::Color::Black)
        return false;

    return true;
}


// Check whether the position is safe for a collectible.
bool Collectible::isWalkable(int x, int y) const
{
    if (!isPathPixel(x, y))
        return false;

    if (!isPathPixel(x - 5, y))
        return false;

    if (!isPathPixel(x + 5, y))
        return false;

    if (!isPathPixel(x, y - 5))
        return false;

    if (!isPathPixel(x, y + 5))
        return false;

    return true;
}


// Place collectibles randomly across the map.
void Collectible::placeCollectibles()
{
    sf::Vector2u mapSize = collisionMap.getSize();

    if (mapSize.x < 40 || mapSize.y < 40)
    {
        std::cout << "Collision map is too small." << std::endl;
        return;
    }

    int minX = 18;
    int minY = 18;

    int maxX = 780;
    int maxY = 580;

    if (mapSize.x < 788)
        maxX = mapSize.x - 8;

    if (mapSize.y < 588)
        maxY = mapSize.y - 8;

    if (maxX <= minX || maxY <= minY)
        return;

    int values[4] = { 10, 15, 20, 25 };

    int attempts = 0;

    while (itemCount < MAX_COLLECTIBLES && attempts < 50000)
    {
        attempts++;

        int x = minX + rand() % (maxX - minX + 1);
        int y = minY + rand() % (maxY - minY + 1);

        // Do not place items on walls.
        if (!isWalkable(x, y))
            continue;

        // Keep the starting area clear.
        float dx = x - 500;
        float dy = y - 280;

        if (dx * dx + dy * dy < 70 * 70)
            continue;

        // Check distance from other collectibles.
        bool tooClose = false;

        for (int i = 0; i < itemCount; i++)
        {
            float distanceX = x - items[i].position.x;
            float distanceY = y - items[i].position.y;

            if (distanceX * distanceX +
                distanceY * distanceY < 44 * 44)
            {
                tooClose = true;
                break;
            }
        }

        if (tooClose)
            continue;

        // Select collectible type.
        int type;

        if (itemCount == 0)
            type = 3;       // 1 Lassi

        else if (itemCount <= 2)
            type = 1;       // 2 Samosas

        else if (itemCount <= 4)
            type = 2;       // 2 Kulfis

        else
            type = 0;       // 27 Jalebis

        items[itemCount].position = { (float)x, (float)y };

        items[itemCount].textureIndex = type;
        items[itemCount].pointValue = values[type];
        items[itemCount].collected = false;

        itemCount++;
    }

    if (itemCount < MAX_COLLECTIBLES)
    {
        std::cout << "Only " << itemCount
            << " collectibles were placed." << std::endl;
    }
}


// Check collision with the player.
void Collectible::checkCollision(
    const sf::FloatRect& playerBounds, Points& points)
{
    float playerLeft = playerBounds.position.x;
    float playerTop = playerBounds.position.y;

    float playerRight = playerLeft + playerBounds.size.x;
    float playerBottom = playerTop + playerBounds.size.y;

    float ITEM_HALF_SIZE = 10;

    for (int i = 0; i < itemCount; i++)
    {
        if (items[i].collected)
            continue;

        float itemLeft = items[i].position.x - ITEM_HALF_SIZE;
        float itemRight = items[i].position.x + ITEM_HALF_SIZE;

        float itemTop = items[i].position.y - ITEM_HALF_SIZE;
        float itemBottom = items[i].position.y + ITEM_HALF_SIZE;

        bool collision =
            playerRight >= itemLeft &&
            playerLeft <= itemRight &&
            playerBottom >= itemTop &&
            playerTop <= itemBottom;

        if (collision)
        {
            items[i].collected = true;

            points.addPoints(items[i].pointValue);
        }
    }
}


// Check whether all collectibles have been collected.
bool Collectible::allCollected() const
{
    if (itemCount == 0)
        return false;

    for (int i = 0; i < itemCount; i++)
    {
        if (!items[i].collected)
            return false;
    }

    return true;
}


// Draw collectibles on the screen.
void Collectible::draw(sf::RenderWindow& window) const
{
    float DESIRED_SIZE = 30;

    for (int i = 0; i < itemCount; i++)
    {
        if (items[i].collected)
            continue;

        int type = items[i].textureIndex;

        sf::Vector2u textureSize = textures[type].getSize();

        if (textureSize.x == 0 || textureSize.y == 0)
            continue;

        sf::Sprite sprite(textures[type]);

        float largestSide = textureSize.x;

        if (textureSize.y > largestSide)
            largestSide = textureSize.y;

        float scale = DESIRED_SIZE / largestSide;

        sprite.setScale({ scale, scale });

        sprite.setOrigin(sprite.getLocalBounds().getCenter());

        sprite.setPosition(items[i].position);

        window.draw(sprite);
    }
}
