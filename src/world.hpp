#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include "player.hpp"

class World
{
public:
	World();
	void createMap(sf::String tile_map[], const int map_width, const int map_height, int tile_width, int tile_height, sf::RenderWindow& window, Player& player_rect, Player& player2_rect, bool& player_tile_collision, bool& player2_tile_collision, int player1_width, int player2_width);
	void playerCollision(Player& player_rect, Player& player2_rect, bool& player_tile_collision, bool& player2_tile_collision, int player1_width, int player2_width);
	sf::Sprite tile;
private:
	sf::Texture tile_set;
	float tile_top;
};

#endif