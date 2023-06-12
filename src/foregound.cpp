#include <SFML/Graphics.hpp>
#include "foreground.hpp"
#include <string>

Foreground::Foreground(std::string foreground_texture_string, float foreground_x, float foreground_y)
{
	// Load foreground texture
	if (!foreground_texture.loadFromFile(foreground_texture_string))
	{
		std::cout << "ERROR:: Cannot load left foreground texture from file" << "\n";
	}
	foreground.setPosition(sf::Vector2f(foreground_x, foreground_y));
	foreground.setTexture(foreground_texture);
}

void Foreground::drawTo(sf::RenderWindow& window)
{
	window.draw(foreground);
}
