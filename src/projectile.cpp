#include <SFML/Graphics.hpp>
#include "projectile.hpp"

Projectile::Projectile(float proj_width, float proj_height, float& proj_x, float& proj_y, sf::Color proj_color)
{
	projectile.setSize(sf::Vector2f(proj_width, proj_height));
	projectile.setPosition(sf::Vector2f(proj_x, proj_y));
	projectile.setFillColor(proj_color);
}