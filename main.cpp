#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
using namespace std;




int main()
{

	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Lahore Dash");

	sf::Texture
		trackTexture;

	if (!trackTexture.loadFromFile(
		"assets/menu_background.jpeg"))
	{
		return 1;
	}



	sf::RectangleShape wall;
	wall.setSize({ 100, 10 });
	wall.setFillColor(sf::Color::Blue);
	wall.setPosition({ 200, 300 });

	Player player;


	while (window.isOpen())
	{
		window.clear(sf::Color(184, 201, 217));
		player.draw(window);
		window.draw(wall);
		window.display();
		while (auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
				
		}
		player.handlemovement(wall);


	}
	cout << "All done!";



}