
#pragma once

#include <SFML/Graphics.hpp>

class Points
{
public:
    Points();

    void addPoints(int amount);
    void reset();
    int getScore() const;
    void draw(sf::RenderWindow& window) const;

private:
    int score;

    void drawDigit(sf::RenderWindow& window, int digit,
        sf::Vector2f position) const;
};
