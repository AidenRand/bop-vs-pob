#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>

class World : public sf::Drawable, public sf::Transformable
{
public:
	World();
	~World();
	bool loadTiles(const std::string& tile_set, sf::Vector2u tile_size, const int* tiles, unsigned int desired_width, usigned int desired_height);

private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

};

#endif