#include "game.hpp"
#include "menu.hpp"

void game(sf::RenderWindow& window, float screen_width, float screen_height)
{
	Menu menu(screen_width, screen_height);

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
		menu.draw(window);
		window.display();
	}
}