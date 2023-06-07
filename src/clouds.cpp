#include "clouds.hpp"
#include <SFML/Graphics.hpp>

Clouds::Clouds()
{
	if (!back_clouds_texture.loadFromFile("content/back-clouds.png"))
	{
		std::cout << "ERROR::Could not load back clouds from file" << "\n";
	}
}

void Clouds::setPos(float clouds_x, float clouds_y)
{
	back_clouds.setTexture(back_clouds_texture);
	back_clouds.setPosition(sf::Vector2f(clouds_x, clouds_y));
}

void Clouds::drawTo(sf::RenderWindow& window)
{
	window.draw(back_clouds);
}

void Clouds::moveTiles(int cloud_scroll_speed, float& dt)
{
	back_clouds.move(cloud_scroll_speed * dt, 0);
}

float Clouds::returnX()
{
	return back_clouds.getPosition().x;
}