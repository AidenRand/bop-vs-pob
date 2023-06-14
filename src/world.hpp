#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include "players.hpp"

class World
{
public:
	World();
	void createMap(sf::String tile_map[], const int map_width, const int map_height, int tile_width, int tile_height, sf::RenderWindow& window, Players& player_rect, bool& player_tile_collision);
	void playerCollision(Players& player_rect, bool& player_tile_collision);
	sf::Sprite tile;
private:
	sf::Texture tile_set;
	float tile_bottom;
	float tile_left;
	float tile_right;
	float tile_top;
};

#endif