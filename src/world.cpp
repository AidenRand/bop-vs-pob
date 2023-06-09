#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "players.hpp"

bool World::loadTiles(const std::string& tile_set, sf::Vector2u tile_size, const int* tiles, unsigned int desired_width, unsigned int desired_height)
{
	if (!m_tileset.loadFromFile(tile_set))
	{
		std::cout << "ERROR:: Cannot load tileset from file" << "\n";
		return false;
	}

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(desired_width * desired_height * 4);


	for (unsigned int i = 0; i < desired_width; ++i)
	{
		for (unsigned int j = 0; j < desired_height; ++j)
		{
			int tile_number = tiles[i + j * desired_width];

			// Find tile position in tileset
			int tu = tile_number % (m_tileset.getSize().x / tile_size.x);
			int tv = tile_number / (m_tileset.getSize().x / tile_size.x);

			// Get pointer to current tile quad
			sf::Vertex* quad = &m_vertices[(i + j * desired_width) * 4];

			// Define four corners of tile
			quad[0].position = sf::Vector2f(i * tile_size.x, j * tile_size.y);
			quad[1].position = sf::Vector2f((i + 1) * tile_size.x, j * tile_size.y);
			quad[2].position = sf::Vector2f((i + 1) * tile_size.x, (j + 1) * tile_size.y);
			quad[3].position = sf::Vector2f(i * tile_size.x, (j + 1) * tile_size.y);

			// Define tiles four texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
			quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
		}
	}
	return true;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.transform.translate(0, 460);

	states.texture = &m_tileset;

	target.draw(m_vertices, states);
}

void World::collision(Players& players)
{
	auto player = players.player;

	if (m_vertices.getBounds().intersects(player.getGlobalBounds()))
	{
		std::cout << "collision" << "\n";
	}
}
