#include "game.hpp"
#include "menu.hpp"
#include <SFML/Graphics.hpp>

void game(sf::RenderWindow& window, float screen_width, float screen_height)
{
	// Add background texture
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

	// Create menu
	Menu menu;
	bool game_running = false;
	int menu_font_size = 30;
	float title_x = 230;
	float title_y = -130;
	menu.createButtons(screen_width, screen_height, menu_font_size);
	menu.createTitle(title_x, title_y);

	// Make delta time
	float dt;
	sf::Clock clock;

	while (window.isOpen())
	{
		// Get delta time
		dt = clock.restart().asSeconds();

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
		menu.animateTitle(0, dt);
		menu.drawTitle(window);
		window.display();
	}
}