#include <SFML/Graphics.hpp>
#include "projectile.hpp"

Projectile::Projectile(int proj_width, int proj_height, sf::Color proj_color)
{
	projectile.setSize(sf::Vector2f(proj_width, proj_height));
	projectile.setFillColor(proj_color);
}

void Projectile::drawTo(sf::RenderWindow& window)
{
	window.draw(projectile);
}

void Projectile::spawnProj(int player_direction)
{
	if (player_direction == -1)
	{
		direction.x -= proj_speed;
	}

	if (player_direction == 1)
	{
		direction.x += proj_speed;
	}

	projectile.move(direction);
}

void Projectile::fireProj()
{

	projectile.move(direction);
}

void Projectile::setPos(float proj_x, float proj_y)
{
	projectile.setPosition(sf::Vector2f(proj_x, proj_y));
}