#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

bool TileMap::loadTiles(const std::string& tile_set, sf::Vector2u tile_size, const int* tiles, unsigned int width, unsigned int height)
{
	if (!m_tileset.loadFromFile(tile_set))
	{
		return false;
	}

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			int tile_number = tiles[i + j * width];

			// Find tile position in tileset image
			int tu = tile_number % (m_tileset.getSize().x / tile_size.x);
			int tv = tile_number / (m_tileset.getSize().x / tile_size.x);

			// Get pointer to current tile quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

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

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &m_tileset;

	target.draw(m_vertices, states);
}