#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "players.hpp"

World::World()
{
	if (!tile_set.loadFromFile("content/dirt-tiles.png"))
	{
		std::cout << "ERROR:: Cannot load tileset from file" << "\n";
	}
	tile.setTexture(tile_set);
}

void World::createMap(sf::String tile_map[], const int map_width, const int map_height, int tile_width, int tile_height, sf::RenderWindow& window, Players& player_rect, bool& player_tile_collision)
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
			playerCollision(player_rect, player_tile_collision);
			window.draw(tile);
		}
	}
}

void World::playerCollision(Players& player_rect, bool& player_tile_collision)
{
	// auto player_bottom = player_rect.player_bottom;
	// auto player_velocity_y = player_rect.velocity.y;
	tile_top = tile.getPosition().y;
	// Detect collision between player and tile
	if (player_rect.player.getGlobalBounds().intersects(tile.getGlobalBounds()))
	{
		player_tile_collision = true;
		player_rect.player.setPosition(sf::Vector2f(player_rect.player.getPosition().x, tile.getPosition().y - 50));
		player_rect.gravity = 0;
	}
	else
	{
		player_rect.gravity = 20;
	}
	std::cout << player_tile_collision << "\n";
	std::cout << player_rect.velocity.x << "\n";


}