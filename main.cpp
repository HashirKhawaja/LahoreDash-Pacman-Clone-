#include <SFML/Graphics.hpp>



int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1080,720 }), "Lahore Dash");

	while (window.isOpen())
	{
		window.clear(sf::Color::Green);
		window.display();
		while (auto event = window.pollEvent())
		{
				if (event->is<sf::Event::Closed>())
				{
					window.close();
				}
				
				
		}

	}


}