#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include <iostream>
using namespace std;


void backgroundimg(sf::RenderWindow& window);
void drawMap(sf::RenderWindow& window);

int main()
{

	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Lahore Dash");

	sf::RectangleShape wall;
	wall.setSize({ 0.1, 0.1 });
	wall.setFillColor(sf::Color::Blue);
	wall.setPosition({ 200, 300 });

	sf::Music backgroundMusic;

	if (!backgroundMusic.openFromFile("assets/Background_music.ogg"))
	{
		cout << "Background music not loaded!" << endl;
		return 0;
	}

	backgroundMusic.setLooping(true);
	backgroundMusic.setVolume(50);
	backgroundMusic.play();

	Player player;

	backgroundimg(window);

	while (window.isOpen())
	{

		window.clear(sf::Color(184, 201, 217));

		drawMap(window);
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

void drawMap(sf::RenderWindow& window)
{
	sf::Texture texture1("assets/Map.jpeg");
	sf::Sprite drawMap(texture1);
	drawMap.setScale({ (800.0f / texture1.getSize().x),(600.0f / texture1.getSize().y) });

	window.draw(drawMap);
}