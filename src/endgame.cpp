#include "endgame.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>

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
	if (player_health <= 0)
	{
		window.draw(endgame_text);
	}
}

void Endgame::resetGame(sf::Keyboard::Key reset_game_button, Player& player_sprite, int& player_health, float& player_x, float& player_y)
{
	if (sf::Keyboard::isKeyPressed(reset_game_button))
	{
		player_sprite.player.setPosition(sf::Vector2f(player_x, player_y));
		player_health = 10;
	}
}