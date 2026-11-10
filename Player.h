#pragma once
#include <SFML/Graphics.hpp>


class Player
{
public:
	Player();

	void handlemovement(sf::RectangleShape& wall);
	void draw(sf::RenderWindow& window);

private:
	sf::Texture texture;
	sf::Sprite shape;
};

