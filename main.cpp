#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Collectible.h"
#include "Points.h"
#include "Enemy.h"
#include <iostream>
using namespace std;

void backgroundimg(sf::RenderWindow& window);

int main()
{

	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Lahore Dash");

	sf::RectangleShape wall;
	wall.setSize({ 0.1f, 0.1f });
	wall.setFillColor(sf::Color::Blue);
	wall.setPosition({ 200, 300 });

	sf::Texture texture1("assets/Map.jpeg");
	sf::Sprite drawMap(texture1);
	drawMap.setScale({ (800.0f / texture1.getSize().x),(600.0f / texture1.getSize().y) });


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
	Enemy enemy1("assets/rickshaw_blue.png", 100, 200);
	Enemy enemy2("assets/rickshaw_green.png", 700, 300);
	Enemy enemy3("assets/rickshaw_red.png", 300, 500);
	Collectible collectibles;
	Points points;
	// Load hearts
	sf::Texture heartsTexture("assets/hearts.png");

	sf::Sprite heart1(heartsTexture);
	sf::Sprite heart2(heartsTexture);
	sf::Sprite heart3(heartsTexture);

	// Divide the image into three hearts
	int heartWidth = heartsTexture.getSize().x / 3;
	int heartHeight = heartsTexture.getSize().y;

	heart1.setTextureRect(sf::IntRect(
		{ 0, 0 }, { heartWidth, heartHeight }));

	heart2.setTextureRect(sf::IntRect(
		{ heartWidth, 0 }, { heartWidth, heartHeight }));

	heart3.setTextureRect(sf::IntRect(
		{ heartWidth * 2, 0 }, { heartWidth, heartHeight }));

	// Set heart sizes
	heart1.setScale({ 0.055f, 0.055f });
	heart2.setScale({ 0.055f, 0.055f });
	heart3.setScale({ 0.055f, 0.055f });

	// Position hearts
	heart1.setPosition({ 640, 10 });
	heart2.setPosition({ 690, 10 });
	heart3.setPosition({ 740, 10 });

	// Lives
	int lives = 3;
	int protectionFrames = 0;

	backgroundimg(window);

	while (window.isOpen())
	{

		while (auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
		{
			backgroundimg(window);
		}
		player.handlemovement(wall);
		sf::FloatRect playerBounds = player.getBounds();
		enemy1.handlemovement(playerBounds);
		enemy2.handlemovement(playerBounds);
		enemy3.handlemovement(playerBounds);
		// Reduce protection time
		if (protectionFrames > 0)
		{
			protectionFrames--;
		}

		// Check enemy collision
		else if (enemy1.checkCollision(playerBounds) ||
			enemy2.checkCollision(playerBounds) ||
			enemy3.checkCollision(playerBounds))
		{
			lives--;

			cout << "Lives remaining: " << lives << endl;

			// Return player to starting position
			player.resetPosition();

			// Temporary protection
			protectionFrames = 90;

			if (lives == 0)
			{
				cout << "GAME OVER!" << endl;

				window.close();
				break;
			}
		}

		collectibles.checkCollision(player.getBounds(), points);
		if (collectibles.allCollected())
		{
			cout << "YOU WIN!" << endl; 
			cout << "Final Score: " << points.getScore() << endl;

			window.close();
			break;
		}

		window.clear(sf::Color(184, 201, 217));
		window.draw(drawMap);
		collectibles.draw(window);
		enemy1.draw(window);
		enemy2.draw(window);
		enemy3.draw(window);
		player.draw(window);
		points.draw(window);
		// Display remaining hearts
		if (lives >= 1)
			window.draw(heart1);

		if (lives >= 2)
			window.draw(heart2);

		if (lives >= 3)
			window.draw(heart3);
		window.draw(wall);
		window.display();

	}

	cout << "All done!";

}
