#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>

class Projectile
{
public:
	Projectile(std::string proj_texture_file);
	void setPos(float proj_x, float proj_y);
	void drawTo(sf::RenderWindow& window);
	void spawnProj(int player_direction);
	void fireProj();
	void killProj(bool& proj_dead, float& screen_width);

private:
	sf::Sprite projectile;
	sf::Texture proj_texture;
	sf::Vector2f direction;
	float proj_speed = 10;
};

#endif