#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "hitbox.hpp"

class Player : public sf::Sprite
{
public:
	Player(std::string player_tileset, float player_width, float& player_height, float player_x, float player_y);
	void drawTo(sf::RenderWindow& window);
	void movePlayer(int player_speed, bool& player_tile_collision, float& dt, int& player_tile_row, int& player_health);
	void movePlayer2(int player_speed, bool& player_tile_collision, float& dt, int& player_tile_row, int& player_health);
	void collision(float screen_width, float player_width, float player_height, float& hitbox_x, float& hitbox_y);
	void attack(int& player_tile_row, int& weak_reload_timer, int& strong_reload_timer, bool& weak_attack, bool& strong_attack);
	void crouchAnimation(int& player_tile_row, bool& player_tile_collision, float& hitbox_y, float& player_height);
	void knockoutAnimation(int& player_tile_row, int& player_health);
	void animatePlayer(int row, float& dt);
	float returnX();
	float returnY();
	int returnScale();
	HitboxSprite player;

	float player_top;
	float player_bottom;
	float player_left;
	float player_right;

	sf::FloatRect player_hitbox;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float gravity = 50.0f;

private:
	sf::Texture player_texture;
	sf::IntRect player_uv_rect;
	float total_time;
	float switch_time = 0.08f;
	sf::Vector2u image_count = sf::Vector2u(8, 1);
	sf::Vector2u current_image;
	int jump_power = 800;
	int play_weak;
	int play_strong;
};

#endif