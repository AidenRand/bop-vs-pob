#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

World::World()
{
	if (!tile_set.loadFromFile("content/dirt-tiles.png"))
	{
		std::cout << "ERROR:: Cannot load tileset from file" << "\n";
	}
	tile.setTexture(tile_set);
}

void World::createMap(sf::String tile_map[], const int map_width, const int map_height, int tile_width, int tile_height, sf::RenderWindow& window, Players& player_rect)
{
	// Loop through tile_map and assign tile texture to tile
	// according to what string is
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j != map_width; j++)
		{
			if (tile_map[i][j] == 'G')
			{
				tile.setTextureRect(sf::IntRect(0 * tile_width, 0 * tile_height, tile_width, tile_height));
			}

			if (tile_map[i][j] == 'B')
			{
				tile.setTextureRect(sf::IntRect(1 * tile_width, 0 * tile_height, tile_width, tile_height));
			}

			if (tile_map[i][j] == '0' || tile_map[i][j] == ' ')
			{
				continue;
			}

			// Set tile position
			tile.setPosition(sf::Vector2f(j * tile_width, i * tile_height));
			playerCollision(player_rect);
			window.draw(tile);
		}
	}
}

void World::playerCollision(Players& player_rect)
{
	auto player = player_rect.player;
	// Detect collision between player and tile
	if (player.getGlobalBounds().intersects(tile.getGlobalBounds()))
	{
	}
}