#include <Sfml/Graphics.hpp>

void backgroundimg(sf::RenderWindow& window)
{
	sf::Texture texture("assets/menu_background.jpeg");
	sf::Sprite background(texture);
	background.setScale({ (800.0f / texture.getSize().x),(600.0f / texture.getSize().y) });

	window.clear();
	window.draw(background);
	window.display();

	while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)))
	{
		if (auto event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		window.clear();
		window.draw(background);
		window.display();
	}
	return;


}