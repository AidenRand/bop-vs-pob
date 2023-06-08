#include "players.hpp"

Players::Players(float player_width, float player_height, float player_x, float player_y)
{
	player.setFillColor(sf::Color::White);
	player.setSize(sf::Vector2f(player_width, player_height));
	player.setPosition(sf::Vector2f(player_x, player_y));
}