#ifndef PLAYER2_HPP
#define PLAYER2_hpp

#include <SFML/Graphics.hpp>
#include "hitbox.hpp"

class Player2 : public sf::Sprite
{
public:
	Player2(std::string p2_tileset, float p2_width, float p2_height, float p2_x, float p2_y);
	void drawTo(sf::RenderWindow& window);
	void animatePlayer(int row, float& dt);
	HitboxSprite player2;
	sf::FloatRect p2_hitbox;
	sf::Vector2f position;
	sf::Vector2f velocity;

private:
	sf::Texture p2_texture;
	sf::IntRect p2_uv_rect;
	float total_time;
	float switch_time = 0.08f;
	sf::Vector2u image_count = sf::Vector2u(8, 1);
	sf::Vector2u current_image;

	float gravity = 50.0f;
};

#endif