#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <SFML/Graphics.hpp>

class Players
{
public:
	Players(float player_width, float player_height, float player_x, float player_y);
	void drawTo(sf::RenderWindow& window);
	void movePlayers(int player_speed, bool& player_tile_collision);
	void tileCollision(bool& player_tile_collision);
	sf::RectangleShape player;
	float player_top;
	float player_bottom;
	float player_left;
	float player_right;
	float step_x = 5;
	float step_y = 5;

private:
	// sf::Vector2f velocity;
};

#endif