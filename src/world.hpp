#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include "players.hpp"

class World
{
public:
	World();
private:
	sf::Sprite tile;
	sf::Texture tile_set;

};

#endif