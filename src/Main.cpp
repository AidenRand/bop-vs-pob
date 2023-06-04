#include "game.hpp"
#include <SFML/Graphics.hpp>

int main()
{
	float screen_width = 960;
	float screen_height = 540;
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Bop vs Pob");
	window.setFramerateLimit(60);

	game(window);

}