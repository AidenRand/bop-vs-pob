#include <SFML/Graphics.hpp>
#include "projectile.hpp"

Projectile::Projectile(std::string proj_texture_file)
{
	if (!proj_texture.loadFromFile(proj_texture_file))
	{
		std::cout << "ERROR:: Cannot load projectile texture from file" << "\n";
	}
	projectile.setTexture(proj_texture);
}

void Projectile::drawTo(sf::RenderWindow& window)
{
	window.draw(projectile);
}

void Projectile::spawnProj(int player_direction)
{
	// Shoot the projectile in the direction the player is facing
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
	// Set projectile position to player position
	projectile.setPosition(sf::Vector2f(proj_x, proj_y));
}

void Projectile::killProj(bool& proj_dead, float& screen_width)
{
	// If projectile goes beyond screen, kill it
	if (projectile.getPosition().x > screen_width || projectile.getPosition().x < 0)
	{
		proj_dead = true;
	}
}