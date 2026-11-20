#include "Player.h"


Player::Player() : texture("assets/player.png"), shape(texture)
{
	shape.setScale({ 0.04f,0.04f });
	shape.setPosition({ 50,50 });
	shape.setOrigin(shape.getLocalBounds().getCenter());
}

void Player::handlemovement(sf::RectangleShape& wall)
{
	float oldx = shape.getPosition().x;
	float oldy = shape.getPosition().y;
	sf::Clock clock;
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
	if (shape.getGlobalBounds().findIntersection(wall.getGlobalBounds()))
	{
		shape.setPosition({ oldx,shape.getPosition().y });
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
	if (shape.getGlobalBounds().findIntersection(wall.getGlobalBounds()))
	{

		shape.setPosition({ shape.getPosition().x,oldy });
	}
	if (shape.getPosition().x > 750)
	{
		shape.setPosition({ 750,shape.getPosition().y });
	}
	if (shape.getPosition().x < 0)
	{
		shape.setPosition({ 0,shape.getPosition().y });
	}
	if (shape.getPosition().y > 540)
	{
		shape.setPosition({ shape.getPosition().x,540 });
	}
	if (shape.getPosition().y < 0)
	{
		shape.setPosition({ shape.getPosition().x,0});
	}

}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}