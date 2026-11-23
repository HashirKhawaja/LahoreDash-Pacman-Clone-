#include "Player.h"


Player::Player() : texture("assets/player.png"), shape(texture), CollisionImage("assets/CollisionMap.png"), Lives("assets/hearts.png"),hearts(Lives)
{
	shape.setScale({ 0.04f,0.04f });
	shape.setPosition({ 500,280 });
	shape.setOrigin(shape.getLocalBounds().getCenter());
	hearts.setTextureRect(sf::IntRect({ 0, 0 },{ (int)Lives.getSize().x, (int)Lives.getSize().y }));
	hearts.setScale({ 0.05f,0.05f });
	hearts.setPosition({ 650, 15 });
	
}

void Player::handlemovement(sf::RectangleShape& wall)
{
	if (Hearts > 0)
	{
		float oldx = shape.getPosition().x;
		float oldy = shape.getPosition().y;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			shape.setRotation(sf::degrees(0));
			shape.setScale({ 0.04f,0.04f });
			shape.move({ 0.15f,0 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			shape.setRotation(sf::degrees(0));
			shape.setScale({ -0.04f,0.04f });
			shape.move({ -0.15,0 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			shape.setScale({ 0.04f,0.04f });
			shape.setRotation(sf::degrees(-90));

			shape.move({ 0,-0.15 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			shape.setRotation(sf::degrees(90));
			shape.setScale({ 0.04f,0.04f });
			shape.move({ 0,0.15 });
		}
		int x = shape.getPosition().x;
		int y = shape.getPosition().y;

		sf::Color pixel = CollisionImage.getPixel({ (unsigned int)x,(unsigned int)y });
		if (pixel == sf::Color::Black)
		{
			shape.setPosition({ oldx,oldy });

		}

		if (shape.getPosition().x > 780)
		{
			shape.setPosition({ 780,shape.getPosition().y });
		}
		if (shape.getPosition().x < 10)
		{
			shape.setPosition({ 10,shape.getPosition().y });
		}
		if (shape.getPosition().y > 570)
		{
			shape.setPosition({ shape.getPosition().x,570 });
		}
		if (shape.getPosition().y < 10)
		{
			shape.setPosition({ shape.getPosition().x,10 });
		}
		if (shape.getGlobalBounds().findIntersection(enemy.getGlobalBounds()))
		{
			if (firsthit|| timer.getElapsedTime().asSeconds() >= 1.5f)
			{
				Hearts -= 1;
				int width = (Lives.getSize().x / 3) * Hearts;
				hearts.setTextureRect(sf::IntRect({ 0, 0 }, { width, (int)Lives.getSize().y }));
				timer.restart();
				firsthit = false;
			}

		}
	}

}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(hearts);
}