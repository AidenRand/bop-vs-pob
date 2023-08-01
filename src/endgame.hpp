#ifndef ENDGAME_HPP
#define ENDGAME_HPP

#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Endgame
{
public:
	Endgame(std::string endgame_text_file, float& endgame_text_x, float& endgame_text_y);
	void drawTo(sf::RenderWindow& window, int& player_health);
	void resetGame(sf::Keyboard::Key reset_game_button, Player& player_sprite, int& player_health, float& player_x, float& player_y);

private:
	sf::Sprite endgame_text;
	sf::Texture endgame_text_texture;
};

#endif