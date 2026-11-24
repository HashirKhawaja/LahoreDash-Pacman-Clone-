
#include "Enemy.h"
#include <iostream>


Enemy::Enemy(const char* imagePath, float startX, float startY) : texture(imagePath), shape(texture), CollisionImage("assets/CollisionMap.png")
{
    shape.setScale({ 0.08f, 0.08f });

    shape.setOrigin(shape.getLocalBounds().getCenter());

    shape.setPosition({ startX, startY });
}


// Check whether a pixel is a path.
bool Enemy::isPathPixel(int x, int y) const
{
    sf::Vector2u mapSize = CollisionImage.getSize();

    if (x < 0 || y < 0 ||
        x >= mapSize.x || y >= mapSize.y)
    {
        return false;
    }

    sf::Color pixel = CollisionImage.getPixel({
        (unsigned int)x, (unsigned int)y
        });

    if (pixel == sf::Color::Black)
        return false;

    return true;
}


// Check the center and nearby pixels.
bool Enemy::isWalkable(int x, int y) const
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


// Find a path and move towards the player.
void Enemy::handlemovement(const sf::FloatRect& playerBounds)
{
    const int GRID_SIZE = 10;
    const int GRID_WIDTH = 90;
    const int GRID_HEIGHT = 60;

    const int TOTAL_CELLS = GRID_WIDTH * GRID_HEIGHT;

    float currentX = shape.getPosition().x;
    float currentY = shape.getPosition().y;

    float playerX = playerBounds.position.x +
        playerBounds.size.x / 2;

    float playerY = playerBounds.position.y +
        playerBounds.size.y / 2;

    // Convert positions into grid coordinates.
    int startX = currentX / GRID_SIZE;
    int startY = currentY / GRID_SIZE;

    int goalX = playerX / GRID_SIZE;
    int goalY = playerY / GRID_SIZE;

    // Keep coordinates inside the grid.
    if (startX < 0 || startX >= GRID_WIDTH ||
        startY < 0 || startY >= GRID_HEIGHT)
        return;

    if (goalX < 0)
        goalX = 0;

    if (goalX >= GRID_WIDTH)
        goalX = GRID_WIDTH - 1;

    if (goalY < 0)
        goalY = 0;

    if (goalY >= GRID_HEIGHT)
        goalY = GRID_HEIGHT - 1;

    // Check whether the player's grid cell is walkable.
    if (!isWalkable(
        goalX * GRID_SIZE + 5,
        goalY * GRID_SIZE + 5))
    {
        bool found = false;

        // Search nearby cells if the target cell is blocked.
        for (int distance = 1; distance <= 3 && !found; distance++)
        {
            for (int y = goalY - distance;
                y <= goalY + distance && !found; y++)
            {
                for (int x = goalX - distance;
                    x <= goalX + distance; x++)
                {
                    if (x < 0 || x >= GRID_WIDTH ||
                        y < 0 || y >= GRID_HEIGHT)
                        continue;

                    if (isWalkable(
                        x * GRID_SIZE + 5,
                        y * GRID_SIZE + 5))
                    {
                        goalX = x;
                        goalY = y;
                        found = true;
                        break;
                    }
                }
            }
        }

        if (!found)
            return;
    }

    if (startX == goalX && startY == goalY)
        return;

    // Arrays used for BFS.
    bool visited[60][90] = {};

    int parentX[60][90];
    int parentY[60][90];

    int queueX[5400];
    int queueY[5400];

    // Initialize parent and visited arrays.
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            parentX[y][x] = -1;
            parentY[y][x] = -1;
        }
    }

    // Possible movement directions:
    // Right, Left, Down, Up.
    int directionX[4] = { 1, -1, 0, 0 };
    int directionY[4] = { 0, 0, 1, -1 };

    int front = 0;
    int back = 0;

    // Add the starting cell to the queue.
    queueX[back] = startX;
    queueY[back] = startY;
    back++;

    visited[startY][startX] = true;

    parentX[startY][startX] = startX;
    parentY[startY][startX] = startY;

    // Start searching for the player's cell.
    while (front < back && !visited[goalY][goalX])
    {
        int currentGridX = queueX[front];
        int currentGridY = queueY[front];

        front++;

        // Check all four directions.
        for (int i = 0; i < 4; i++)
        {
            int nextX = currentGridX + directionX[i];
            int nextY = currentGridY + directionY[i];

            // Check grid boundaries.
            if (nextX < 0 || nextX >= GRID_WIDTH ||
                nextY < 0 || nextY >= GRID_HEIGHT)
                continue;

            // Ignore already visited cells.
            if (visited[nextY][nextX])
                continue;

            // Check whether the next cell is walkable.
            if (!isWalkable(
                nextX * GRID_SIZE + 5,
                nextY * GRID_SIZE + 5))
                continue;

            visited[nextY][nextX] = true;

            parentX[nextY][nextX] = currentGridX;
            parentY[nextY][nextX] = currentGridY;

            queueX[back] = nextX;
            queueY[back] = nextY;
            back++;
        }
    }

    // If no route was found, do not move.
    if (!visited[goalY][goalX])
        return;

    // Trace the path backwards to find the next cell.
    int nextX = goalX;
    int nextY = goalY;

    while (parentX[nextY][nextX] != startX ||
        parentY[nextY][nextX] != startY)
    {
        int previousX = parentX[nextY][nextX];
        int previousY = parentY[nextY][nextX];

        if (previousX == -1 || previousY == -1)
            return;

        nextX = previousX;
        nextY = previousY;
    }

    // Move towards the next cell.
    float speed = 0.19f;

    float centerX = startX * GRID_SIZE + 5;
    float centerY = startY * GRID_SIZE + 5;

    float destinationX = nextX * GRID_SIZE + 5;
    float destinationY = nextY * GRID_SIZE + 5;

    // If the next cell is horizontal, first align Y.
    if (nextX != startX)
    {
        if (currentY < centerY - speed)
        {
            shape.move({ 0, speed });
            return;
        }

        if (currentY > centerY + speed)
        {
            shape.move({ 0, -speed });
            return;
        }

        // Move right or left.
        if (currentX < destinationX)
        {
            float distance = destinationX - currentX;

            if (distance < speed)
                shape.move({ distance, 0 });
            else
                shape.move({ speed, 0 });
        }
        else if (currentX > destinationX)
        {
            float distance = currentX - destinationX;

            if (distance < speed)
                shape.move({ -distance, 0 });
            else
                shape.move({ -speed, 0 });
        }
    }

    // If the next cell is vertical, first align X.
    else
    {
        if (currentX < centerX - speed)
        {
            shape.move({ speed, 0 });
            return;
        }

        if (currentX > centerX + speed)
        {
            shape.move({ -speed, 0 });
            return;
        }

        // Move up or down.
        if (currentY < destinationY)
        {
            float distance = destinationY - currentY;

            if (distance < speed)
                shape.move({ 0, distance });
            else
                shape.move({ 0, speed });
        }
        else if (currentY > destinationY)
        {
            float distance = currentY - destinationY;

            if (distance < speed)
                shape.move({ 0, -distance });
            else
                shape.move({ 0, -speed });
        }
    }
}


// Check collision with player.

bool Enemy::checkCollision(const sf::FloatRect& playerBounds) const
{
    sf::FloatRect enemyBounds = shape.getGlobalBounds();

    // Reduce player collision box.
    float playerWidth = playerBounds.size.x * 0.60f;
    float playerHeight = playerBounds.size.y * 0.60f;

    float playerLeft = playerBounds.position.x +
        (playerBounds.size.x - playerWidth) / 2;

    float playerTop = playerBounds.position.y +
        (playerBounds.size.y - playerHeight) / 2;

    float playerRight = playerLeft + playerWidth;
    float playerBottom = playerTop + playerHeight;

    // Reduce rickshaw collision box.
    float enemyWidth = enemyBounds.size.x * 0.80f;
    float enemyHeight = enemyBounds.size.y * 0.80f;

    float enemyLeft = enemyBounds.position.x +
        (enemyBounds.size.x - enemyWidth) / 2;

    float enemyTop = enemyBounds.position.y +
        (enemyBounds.size.y - enemyHeight) / 2;

    float enemyRight = enemyLeft + enemyWidth;
    float enemyBottom = enemyTop + enemyHeight;

    // Check actual overlap.
    if (playerRight >= enemyLeft &&
        playerLeft <= enemyRight &&
        playerBottom >= enemyTop &&
        playerTop <= enemyBottom)
    {
        return true;
    }

    return false;
}


// Draw the enemy.
void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
