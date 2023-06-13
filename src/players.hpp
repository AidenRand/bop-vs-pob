#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <SFML/Graphics.hpp>

class Players
{
public:
	Players(float player_width, float player_height, float player_x, float player_y);
	void drawTo(sf::RenderWindow& window);
	void movePlayers(int player_speed);
	sf::RectangleShape player;
	sf::Vector2f velocity;
};

#endif