#include "background.hpp"

Background::Background(float background_x, float background_y, float screen_width, float screen_height)
{
	if (!background_texture.loadFromFile("content/pixil-frame-0(121).png"))
	{
		std::cout << "ERROR::Could not load background from file" << "\n";
	}
	background.setTexture(background_texture);
	background.setPosition(sf::Vector2f(background_x, background_y));
}