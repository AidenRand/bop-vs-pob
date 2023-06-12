#include <SFML/Graphics.hpp>
#include "foreground.hpp"

Foreground::Foreground(float foreground_x, float foreground_y, sf::Texture foreground_texture)
{
	foreground.setPosition(sf::Vector2f(foreground_x, foreground_y));
	foreground.setTexture(foreground_texture);
}

void Foreground::drawTo(sf::RenderWindow& window)
{
	window.draw(foreground);
}
