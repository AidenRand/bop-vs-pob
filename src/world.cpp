#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "players.hpp"

World::World()
{
	if (!tile_set.loadFromFile("content/ground-tileset.png"))
	{
		std::cout << "ERROR:: Cannot load tileset from file" << "\n";
	}
}