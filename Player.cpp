#include "Player.h"


Player::Player() : texture("assets/player.png"), shape(texture), CollisionImage("assets/CollisionMap.png")
{
	shape.setScale({ 0.04f,0.04f });
	shape.setPosition({ 35,385 });
	shape.setOrigin(shape.getLocalBounds().getCenter());
}
sf::FloatRect Player::getBounds() const
{
	return shape.getGlobalBounds();
}

void Player::handlemovement(sf::RectangleShape& wall)
{
	float oldx = shape.getPosition().x;
	float oldy = shape.getPosition().y;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		shape.setRotation(sf::degrees(0));
		shape.setScale({ 0.04f,0.04f });
		shape.move({ 0.15f,0 });
		shape.move({ 0.20f,0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		shape.setRotation(sf::degrees(0));
		shape.setScale({ -0.04f,0.04f });
		shape.move({ -0.15,0 });
		shape.move({ -0.20,0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		shape.setScale({ 0.04f,0.04f });
		shape.setRotation(sf::degrees(-90));

		shape.move({ 0,-0.15 });
		shape.move({ 0,-0.20 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		shape.setRotation(sf::degrees(90));
		shape.setScale({ 0.04f,0.04f });
		shape.move({ 0,0.15 });
		shape.move({ 0,0.20 });
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

}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Player::resetPosition(int lives)
{
	if (lives == 2)
	{
		shape.setPosition({ 745,128 });
	}

	else if (lives == 1)
	{
		shape.setPosition({ 670,500 });
	}
}