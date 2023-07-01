#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include "player.hpp"

class World
{
public:
	World();
	void createMap(sf::String tile_map[], const int map_width, const int map_height, int tile_width, int tile_height, sf::RenderWindow& window, Player& p1_rect, Player& p2_rect, bool& player_tile_collision, bool& p2_tile_collision, int player_width);
	void playerCollision(Player& p1_rect, bool& player1_tile_collision, int player_width);
	void player2Collision(Player& p2_rect, bool& player2_tile_collision, int player_width);
	sf::Sprite tile;
private:
	sf::Texture tile_set;
	float tile_top;
};

#endif