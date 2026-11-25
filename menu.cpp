#include <SFML/Graphics.hpp>
void backgroundimg(sf::RenderWindow& window)
{
	sf::Texture texture("assets/menu_background.jpeg");
	sf::Sprite background(texture);
	background.setScale({ (800.0f / texture.getSize().x),(600.0f / texture.getSize().y) });

	sf::Font font("C:/Windows/Fonts/arial.ttf");

	sf::RectangleShape startButton({ 220, 50 });
	sf::RectangleShape highScoreButton({ 220, 50 });
	sf::RectangleShape quitButton({ 220, 50 });


	startButton.setPosition({ 400, 340 });
	highScoreButton.setPosition({ 400, 405 });
	quitButton.setPosition({ 400, 470 });

	startButton.setFillColor(sf::Color(65, 30, 15));
	highScoreButton.setFillColor(sf::Color(65, 30, 15));
	quitButton.setFillColor(sf::Color(65, 30, 15));

	startButton.setOutlineColor(sf::Color(255, 190, 55));
	highScoreButton.setOutlineColor(sf::Color(255, 190, 55));
	quitButton.setOutlineColor(sf::Color(255, 190, 55));

	startButton.setOutlineThickness(3);
	highScoreButton.setOutlineThickness(3);
	quitButton.setOutlineThickness(3);

	sf::Text startText(font, "START");
	sf::Text highScoreText(font, "HIGH SCORE");
	sf::Text quitText(font, "QUIT");

	startText.setCharacterSize(23);
	highScoreText.setCharacterSize(23);
	quitText.setCharacterSize(23);

	startText.setFillColor(sf::Color::White);
	highScoreText.setFillColor(sf::Color::White);
	quitText.setFillColor(sf::Color::White);

	startText.setOrigin(startText.getLocalBounds().getCenter());
	highScoreText.setOrigin(highScoreText.getLocalBounds().getCenter());
	quitText.setOrigin(quitText.getLocalBounds().getCenter());

	startText.setPosition({ 510, 365 });
	highScoreText.setPosition({ 510, 430 });
	quitText.setPosition({ 510, 495 });

	window.clear();
	window.draw(background);
	window.display();
	
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                return;
            }

            if (const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButton->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(mouseButton->position);

                    if (startButton.getGlobalBounds().contains(mousePosition))
                    {
                        return;
                    }
                }
            }
        }

        // Press Enter to start
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            return;
        }

        // Draw menu
        window.clear();

        window.draw(background);

        window.draw(startButton);
        window.draw(highScoreButton);
        window.draw(quitButton);

        window.draw(startText);
        window.draw(highScoreText);
        window.draw(quitText);

        window.display();
    }

    return;

}
