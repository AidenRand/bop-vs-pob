#ifndef ENDGAME_HPP
#define ENDGAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.hpp"

class Endgame
{
public:
	Endgame(std::string endgame_text_file, float& endgame_text_x, float& endgame_text_y);
	void drawTo(sf::RenderWindow& window, int& player_health);
	void resetGame(sf::Keyboard::Key reset_game_button, Player& player_1, Player& player_2, int& player1_health, int& player2_health, float& player1_x, float& player1_y, float& player2_x, float& player2_y);

private:
	sf::Sprite endgame_text;
	sf::Texture endgame_text_texture;
};

#endif