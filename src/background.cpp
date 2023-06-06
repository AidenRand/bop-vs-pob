#include "background.hpp"

Background::Background()
{
	if (!background_texture.loadFromFile("content/bop-vs-pob-bckgr.png"))
	{
		std::cout << "ERROR::Could not load background from file" << "\n";
	}
}

void Background::setPos(float background_x, float background_y, float screen_width)
{
	background.setTexture(background_texture);

	background.setPosition(sf::Vector2f(background_x, background_y));
	std::cout << screen_width;
}

void Background::drawTo(sf::RenderWindow& window)
{
	window.draw(background);
}

void Background::moveTiles()
{
	background.move(5, 0);
}

float Background::returnX()
{
	return background.getPosition().x;
}