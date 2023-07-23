#include "endgame.hpp"
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
	if (player_health == 0)
	{
		window.draw(endgame_text);
	}
}