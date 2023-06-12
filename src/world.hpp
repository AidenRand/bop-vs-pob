#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include "players.hpp"

class World
{
public:
	World();
	void createMap(sf::String tile_map[], const int map_width, const int map_height, sf::RenderWindow& window, Players& player_rect);
	void playerCollision(Players& player_rect);
	sf::Sprite tile;
private:
	sf::Texture tile_set;
};

#endif