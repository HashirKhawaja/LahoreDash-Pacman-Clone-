
#include "Points.h"
#include <string>

Points::Points()
{
    score = 0;
}


// Add points.
void Points::addPoints(int amount)
{
    if (amount > 0)
        score += amount;
}


// Reset score.
void Points::reset()
{
    score = 0;
}


// Return score.
int Points::getScore() const
{
    return score;
}


// Draw one digit.
void Points::drawDigit(sf::RenderWindow& window, int digit,
    sf::Vector2f position) const
{
    const char* patterns[10] =
    {
        "1111110",
        "0110000",
        "1101101",
        "1111001",
        "0110011",
        "1011011",
        "1011111",
        "1110000",
        "1111111",
        "1111011"
    };

    if (digit < 0 || digit > 9)
        return;

    float x[7] = { 4, 16, 16, 4, 0, 0, 4 };
    float y[7] = { 0, 3, 17, 28, 17, 3, 14 };

    float width[7] = { 12, 4, 4, 12, 4, 4, 12 };
    float height[7] = { 4, 11, 11, 4, 11, 11, 4 };

    for (int i = 0; i < 7; i++)
    {
        if (patterns[digit][i] == '1')
        {
            sf::RectangleShape segment;

            segment.setSize({ width[i], height[i] });

            segment.setPosition({
                position.x + x[i],
                position.y + y[i]
                });

            segment.setFillColor(sf::Color(255, 190, 55));

            window.draw(segment);
        }
    }
}


// Draw score panel.
void Points::draw(sf::RenderWindow& window) const
{
    std::string scoreText = std::to_string(score);

    float panelWidth = 30;

    for (unsigned int i = 0; i < scoreText.length(); i++)
    {
        panelWidth += 25;
    }

    sf::RectangleShape panel({ panelWidth, 50 });

    panel.setPosition({ 12, 12 });

    panel.setFillColor(sf::Color(20, 20, 28, 220));

    panel.setOutlineColor(sf::Color(235, 165, 45));

    panel.setOutlineThickness(2);

    window.draw(panel);

    float x = 25;

    for (unsigned int i = 0; i < scoreText.length(); i++)
    {
        int digit = scoreText[i] - '0';

        sf::Vector2f position(x, 21);

        drawDigit(window, digit, position);

        x += 25;
    }
}
