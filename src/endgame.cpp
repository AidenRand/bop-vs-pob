#include "endgame.hpp"
#include <SFML/Graphics.hpp>
#include "player.hpp"

Endgame::Endgame(std::string endgame_text_file, float& endgame_text_x, float& endgame_text_y)
{
	if (!endgame_text_texture.loadFromFile(endgame_text_file))
	{
		std::cout << "ERROR:: Cannot load endgame text from file"
			<< "\n";
	}
	endgame_text.setTexture(endgame_text_texture);
	endgame_text.setPosition(sf::Vector2f(endgame_text_x, endgame_text_y));
}

void Endgame::drawTo(sf::RenderWindow& window, int& player_health)
{
	if (player_health == 0)
	{
		window.draw(endgame_text);
	}
}

void Endgame::resetGame(sf::Keyboard::Key reset_game_button, Player& player_1, Player& player_2, int& player1_health, int& player2_health, float& player1_x, float& player1_y, float& player2_x, float& player2_y)
{
	if (player1_health == 0 || player2_health == 0)
	{
		if (sf::Keyboard::isKeyPressed(reset_game_button))
		{
			player1_x = 100;
			player1_y = 300;
			player2_x = 800;
			player2_y = 300;
			player_1.player.setPosition(sf::Vector2f(player1_x, player1_y));
			player_2.player.setPosition(sf::Vector2f(player2_x, player2_y));
			player1_health = 10;
			player2_health = 10;
		}
	}
}