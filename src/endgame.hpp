#ifndef ENDGAME_HPP
#define ENDGAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Endgame
{
public:
	Endgame(std::string endgame_text_file, float& endgame_text_x, float& endgame_text_y);
	void drawTo(sf::RenderWindow& window, int& player_health);

private:
	sf::Sprite endgame_text;
	sf::Texture endgame_text_texture;
};

#endif