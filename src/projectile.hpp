#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "player1.hpp"

class Projectile
{
public:
	Projectile(int proj_width, int proj_height, sf::Color proj_color);
	void setPos(float proj_x, float proj_y);
	void drawTo(sf::RenderWindow& window);
	void spawnProj(int player_direction);
	void fireProj();

private:
	sf::RectangleShape projectile;
	sf::Vector2f direction;
	float proj_speed = 5;
};

#endif