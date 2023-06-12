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
	tile.setTexture(tile_set);
}

void World::createMap(sf::String tile_map[], const int map_width, const int map_height)
{
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j != map_width; j++)
		{
			if (tile_map[i][j] == 'G')
			{
				tile.setTextureRect(sf::IntRect(0 * 32, 0 * 32, 32, 32));
			}

			if (tile_map[i][j] == 'M')
			{
				tile.setTextureRect(sf::IntRect(1 * 32, 0 * 32, 32, 32));
			}

			if (tile_map[i][j] == '0' || tile_map[i][j] == ' ')
			{
				continue;
			}

			tile.setPosition(sf::Vector2f(j * 32, i * 32));
		}
	}
}