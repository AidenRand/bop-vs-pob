#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <SFML/Graphics.hpp>

class Players
{
public:
	Players(float player_width, float player_height, float player_x, float player_y);
	void drawTo(sf::RenderWindow& window);
	void movePlayers(int player_speed);
	void tileCollision();
	sf::RectangleShape player;
	float player_top;
	float player_bottom;
	float player_left;
	float player_right;

	sf::Vector2f position;
	sf::Vector2f velocity;
	float gravity = 0;

private:
	// sf::Vector2f velocity;
};

#endif