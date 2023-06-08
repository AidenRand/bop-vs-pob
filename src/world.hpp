#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include "players.hpp"

class World : public sf::Drawable, public sf::Transformable
{
public:
	bool loadTiles(const std::string& tile_set, sf::Vector2u tile_size, const int* tiles, unsigned int desired_width, unsigned int desired_height);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void collision(Players& players);
private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

};

#endif