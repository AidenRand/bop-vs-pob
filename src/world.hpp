#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include <string>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	bool loadTiles(const std::string& tile_set, sf::Vector2u tile_size, const int* tiles, unsigned int width, unsigned int height);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};

#endif