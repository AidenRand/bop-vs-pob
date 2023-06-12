#ifndef FOREGROUND_HPP
#define FOREGROUND_HPP

#include <SFML/Graphics.hpp>

class Foreground
{
public:
	Foreground(std::string foreground_texture_string, float foreground_x, float foreground_y);
	void drawTo(sf::RenderWindow& window);

private:
	sf::Sprite foreground;
	sf::Texture foreground_texture;
};

#endif