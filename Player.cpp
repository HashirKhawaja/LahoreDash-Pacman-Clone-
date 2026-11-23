#include "Player.h"

Player::Player() : texture("assets/player.png"), shape(texture), CollisionImage("assets/CollisionMap.png"), Lives("assets/hearts.png"), hearts(Lives)
{
	shape.setScale({ 0.04f, 0.04f });
	shape.setPosition({ 500.0f, 280.0f });
	shape.setOrigin(shape.getLocalBounds().getCenter());
	hearts.setTextureRect(sf::IntRect({ 0, 0 }, { (int)Lives.getSize().x, (int)Lives.getSize().y }));
	hearts.setScale({ 0.05f, 0.05f });
	hearts.setPosition({ 650.0f, 15.0f });
}

sf::FloatRect Player::getBounds() const
{
	return shape.getGlobalBounds();
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
			shape.setScale({ 0.04f, 0.04f });
			shape.move({ 0.20f, 0.0f });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			shape.setRotation(sf::degrees(0));
			shape.setScale({ -0.04f, 0.04f });
			shape.move({ -0.20f, 0.0f });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			shape.setScale({ 0.04f, 0.04f });
			shape.setRotation(sf::degrees(-90));
			shape.move({ 0.0f, -0.20f });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			shape.setRotation(sf::degrees(90));
			shape.setScale({ 0.04f, 0.04f });
			shape.move({ 0.0f, 0.20f });
		}
		int x = (int)shape.getPosition().x;
		int y = (int)shape.getPosition().y;

		sf::Color pixel = CollisionImage.getPixel({ (unsigned int)x, (unsigned int)y });
		if (pixel == sf::Color::Black)
		{
			shape.setPosition({ oldx, oldy });
		}

		if (shape.getPosition().x > 780.0f)
		{
			shape.setPosition({ 780.0f, shape.getPosition().y });
		}
		if (shape.getPosition().x < 10.0f)
		{
			shape.setPosition({ 10.0f, shape.getPosition().y });
		}
		if (shape.getPosition().y > 570.0f)
		{
			shape.setPosition({ shape.getPosition().x, 570.0f });
		}
		if (shape.getPosition().y < 10.0f)
		{
			shape.setPosition({ shape.getPosition().x, 10.0f });
		}
	}
}

void Player::loseLife()
{
	if (firsthit || timer.getElapsedTime().asSeconds() >= 1.5f)
	{
		Hearts -= 1;
		int width = (Lives.getSize().x / 3) * Hearts;
		if (width < 0)
			width = 0;
		hearts.setTextureRect(sf::IntRect({ 0, 0 }, { width, (int)Lives.getSize().y }));
		timer.restart();
		firsthit = false;
	}
}

int Player::getHearts() const
{
	return Hearts;
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(hearts);
}
