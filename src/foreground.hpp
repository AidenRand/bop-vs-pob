#ifndef FOREGROUND_HPP
#define FOREGROUND_HPP

#include <SFML/Graphics.hpp>

class Foreground
{
public:
	Foreground(float foreground_x, float foreground_y, sf::Texture foreground_texture);
	void drawTo(sf::RenderWindow& window);

private:
	sf::Sprite foreground;
};

#endif