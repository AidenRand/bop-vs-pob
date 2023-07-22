#include "endgame.hpp"
#include <SFML/Graphics.hpp>

Endgame::Endgame(std::string endgame_text_file)
{
	if (!endgame_text_texture.loadFromFile(endgame_text_file))
	{
		std::cout << "ERROR:: Cannot load endgame text from file"
			<< "\n";
	}
}

void Endgame::drawTo(sf::RenderWindow& window)
{
	window.draw(endgame_text);
}