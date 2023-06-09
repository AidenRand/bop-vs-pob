#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <SFML/Graphics.hpp>

class Players
{
public:
	Players(float player_width, float player_height, float player_x, float player_y);
	void drawTo(sf::RenderWindow& window);
	void movePlayers();
	sf::RectangleShape player;

private:
};

#endif