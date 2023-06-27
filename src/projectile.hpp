#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

class Projectile
{
public:
	Projectile(float proj_width, float proj_height, float& proj_x, float& proj_y, sf::Color proj_color);

private:
	sf::RectangleShape projectile;
};

#endif