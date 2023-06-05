#include "game.hpp"
#include "menu.hpp"
#include <SFML/Graphics.hpp>

void game(sf::RenderWindow& window, float screen_width, float screen_height)
{
	sf::Texture background_texture;
	sf::Sprite background;
	if (!background_texture.loadFromFile("content/bop-vs-pob-bckgr.png"))
	{
		std::cout << "ERROR::Could not load background from file" << "\n";
	}

	background.setTexture(background_texture);
	float background_x = 0;
	float background_y = 0;
	background.setPosition(sf::Vector2f(background_x, background_y));

	Menu menu(screen_width, screen_height);
	bool game_running = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		window.draw(background);
		menu.draw(window);
		menu.moveUp();
		menu.moveDown();
		menu.closeGame(window);
		menu.playGame(game_running);
		window.display();
	}
}