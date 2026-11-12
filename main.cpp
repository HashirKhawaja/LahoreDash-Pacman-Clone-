#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
using namespace std;




int main()
{
	sf::RectangleShape wall;
	wall.setSize({ 100, 10 });
	wall.setFillColor(sf::Color::Blue);
	wall.setPosition({ 200, 300 });

	sf::Music backgroundMusic;

	if (!backgroundMusic.openFromFile("assets/Background_music.ogg"))
	{
		cout << "Background music not loaded!" << endl;
		return 1;
	}

	backgroundMusic.setLooping(true);
	backgroundMusic.setVolume(50);
	backgroundMusic.play();

	Player player;

	void backgroundimg(sf::RenderWindow & window);

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