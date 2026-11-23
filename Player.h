#pragma once
#include <SFML/Graphics.hpp>


class Player
{
public:
	Player();
	sf::FloatRect getBounds() const;
	void handlemovement(sf::RectangleShape& wall);
	void loseLife();
	int getHearts() const;
	void draw(sf::RenderWindow& window);

private:
	sf::Texture texture;
	sf::Sprite shape;
	sf::Image CollisionImage;
	int Hearts = 3;
	sf::Texture Lives;
	sf::Sprite hearts;
	sf::Clock timer;
	bool firsthit = true;
};

