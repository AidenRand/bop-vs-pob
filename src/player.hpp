#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "hitbox.hpp"
#include "projectile.hpp"
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite
{
public:
	Player(std::string player_tileset, float player_width, float& player_height, float player_x, float player_y, int player_number);
	void drawTo(sf::RenderWindow& window);
	void movePlayer(int player_speed, bool& player_tile_collision, float& dt, int& player_tile_row, int& player_health, sf::Keyboard::Key move_left_key, sf::Keyboard::Key move_right_key, sf::Keyboard::Key jump_key, sf::Keyboard::Key crouch_key);
	void collision(float screen_width, float player_width, float player_height, float& hitbox_x, float& hitbox_y, float hitbox_width);
	void attack(int& player_tile_row, int& weak_reload_timer, int& strong_reload_timer, bool& weak_attack, bool& strong_attack, sf::Keyboard::Key weak_attack_key, sf::Keyboard::Key strong_attack_key);
	void playerPlayerCollision(Player& player_rect, sf::Keyboard::Key move_left_key, sf::Keyboard::Key move_right_key, float player_width);
	void attackCollision(Player& player_rect, bool& weak_attack, bool& player_hit_status, Projectile& proj_rect);
	void crouchAnimation(int& player_tile_row, bool& player_tile_collision, float& hitbox_y, float& player_height, sf::Keyboard::Key crouch_key);
	void knockoutAnimation(int& player_tile_row, int& player_health);
	void knockbackAnimation(bool& player_hit_status, int& player_tile_row, int player_direction);
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
	int jump_power = 650;
	int play_weak = 0;
	int play_strong = 0;
	int play_knockback = 0;
};

#endif