#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <SFML/Graphics.hpp>

class Players
{
public:
	Players(float player_width, float player_height, float player_x, float player_y);
	void drawTo(sf::RenderWindow& window);
	void movePlayers(int player_speed, bool& player_tile_collision, float& dt, int& player_tile_row);
	void collision(float screen_width, int player_width, int player_height);
	void attack(int& player_tile_row, int& weak_reload_timer, int& strong_reload_timer, bool& weak_attack, bool& strong_attack);
	void crouchAnimation(int& player_tile_row);
	void animatePlayer(int row, float& dt);
	sf::Sprite player;

	float player_top;
	float player_bottom;
	float player_left;
	float player_right;

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