#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <SFML/Graphics.hpp>

class Players
{
public:
	Players(float player_width, float player_height, float player_x, float player_y);

private:
	sf::RectangleShape player;
};

#endif