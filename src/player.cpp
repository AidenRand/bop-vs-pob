#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player(std::string player_tileset, float player_width, float& player_height, float player_x, float player_y, int player_number)
{
	player.setOrigin(player_width / 2, player_height / 2);
	player.setPosition(sf::Vector2f(player_x, player_y));

	// Set starting facing direction based on what player it is
	if (player_number == 2)
	{
		player.setScale(-1, 1);
	}

	// Load texture from file
	if (!player_texture.loadFromFile(player_tileset))
	{
		std::cout << "ERROR:: Cannot load player tileset from file"
				  << "\n";
	}

	// Start at beginning of tileset
	total_time = 0.0f;
	current_image.x = 0;

	// Get size of individual tile
	player_uv_rect.width = player_texture.getSize().x / float(image_count.x);
	player_uv_rect.height = (player_height) / float(image_count.y);
}

void Player::drawTo(sf::RenderWindow& window)
{
	window.draw(player);
	player.setTexture(player_texture, true);
}

void Player::movePlayer(int player_speed, bool& player_tile_collision, float& dt, int& player_tile_row, int& player_health, sf::Keyboard::Key move_left_key, sf::Keyboard::Key move_right_key, sf::Keyboard::Key jump_key, sf::Keyboard::Key crouch_key)
{
	velocity.x = 0;
	player_tile_row = 0;

	if (player_health > 0)
	{
		// If player is colliding with tile set y vel to zero
		if (player_tile_collision)
		{
			velocity.y = 0;
			gravity = 0;
			if (sf::Keyboard::isKeyPressed(jump_key) && !sf::Keyboard::isKeyPressed(crouch_key))
			{
				velocity.y -= jump_power;
			}
		}
		// If player is not colliding with tile increase y vel until collision
		else
		{
			gravity = 50;
			velocity.y += gravity;
		}

		if (!sf::Keyboard::isKeyPressed(crouch_key))
		{
			// If right key is pressed, move right
			if (sf::Keyboard::isKeyPressed(move_right_key) && !sf::Keyboard::isKeyPressed(move_left_key))
			{
				velocity.x = player_speed;
				player_tile_row = 1;
				player.setScale(1, 1);
			}

			// If left key is pressed, move left
			if (sf::Keyboard::isKeyPressed(move_left_key) && !sf::Keyboard::isKeyPressed(move_right_key))
			{
				velocity.x = -player_speed;
				player_tile_row = 1;
				player.setScale(-1, 1);
			}
		}
	}

	player.move(velocity * dt);
}

void Player::collision(float screen_width, float player_width, float player_height, float& hitbox_x, float& hitbox_y, float hitbox_width)
{
	// Get sides of player
	player_top = player.getPosition().y;
	player_bottom = player.getPosition().y + player_height / 2;
	player_left = player.getPosition().x;
	player_right = player.getPosition().x + player_width / 2;

	player.setHitbox({ hitbox_x, hitbox_y, hitbox_width, player_height });

	//  If player goes beyond screen borders, set player position
	// to just before screen border
	if (player_right > screen_width)
	{
		player.setPosition(screen_width - player_width / 2, player.getPosition().y);
	}
	else if (player_left < player_width / 2)
	{
		player.setPosition(player_width / 2, player.getPosition().y);
	}
}

void Player::playerPlayerCollision(Player& player_rect, sf::Keyboard::Key move_left_key, sf::Keyboard::Key move_right_key, float player_width)
{
	// Get left and right of player 2
	auto player2_left = player_rect.player.getPosition().x - player_width;
	auto player2_right = player_rect.player.getPosition().x + player_width;
	auto player_2 = player_rect.player;

	if (player_rect.player.getGlobalBounds().intersects(player.getGlobalBounds()))
	{
		// If player is moving and collides with other player,
		// Set player position to just before collision with other player
		if (sf::Keyboard::isKeyPressed(move_right_key) && !sf::Keyboard::isKeyPressed(move_left_key))
		{
			player.setPosition(player2_left, player.getPosition().y);
		}
		if (sf::Keyboard::isKeyPressed(move_left_key) && !sf::Keyboard::isKeyPressed(move_right_key))
		{
			player.setPosition(player2_right, player.getPosition().y);
		}
	}
}

void Player::attack(int& player_tile_row, int& weak_reload_timer, int& strong_reload_timer, bool& weak_attack, bool& strong_attack, sf::Keyboard::Key weak_attack_key, sf::Keyboard::Key strong_attack_key)
{

	weak_attack = false;
	strong_attack = false;
	// If reload timer equals zero, allow attack
	if (weak_reload_timer == 0)
	{
		if (strong_attack == false)
		{
			if (sf::Keyboard::isKeyPressed(weak_attack_key))
			{
				weak_reload_timer += 30;
				play_weak = 30;
				weak_attack = true;
			}
		}
	}
	// Play weak attack animation if play weak is greater than zero
	else if (play_weak > 0)
	{
		play_weak--;
		player_tile_row = 3;
	}
	else
	{
		weak_reload_timer--;
	}

	// If strong attack reload timer equals zero, allow attack
	if (strong_reload_timer == 0)
	{
		if (weak_attack == false)
			if (sf::Keyboard::isKeyPressed(strong_attack_key))
			{
				strong_reload_timer += 100;
				play_strong = 30;
				strong_attack = true;
			}
	}
	else if (play_strong > 0)
	{
		play_strong--;
		player_tile_row = 2;
	}
	else
	{
		strong_reload_timer--;
	}
}

void Player::attackCollision(Player& player_rect, bool& weak_attack, bool& player_hit_status, Projectile& proj_rect)
{
	auto player_proj = proj_rect.projectile;

	// If player hitboxes are intersecting, register attacks when attacks are true
	if (player_rect.player.getGlobalHitbox().intersects(player.getGlobalHitbox()))
	{
		if (weak_attack)
		{
			play_knockback = 25;
		}
	}

	if (proj_rect.projectile.getGlobalBounds().intersects(player_rect.player.getGlobalBounds()))
	{
		std::cout << "collision"
				  << "\n";
		play_knockback = 50;
		std::cout << play_knockback << "\n";
	}

	// Play the knockback animation if play_knockback is greater than zero
	if (play_knockback > 0)
	{
		player_hit_status = true;
		play_knockback--;
	}
}

void Player::crouchAnimation(int& player_tile_row, bool& player_tile_collision, float& hitbox_y, float& player_height, sf::Keyboard::Key crouch_key)
{
	player_height = 96;
	hitbox_y = 0;
	// When left shift is pressed crouch and don't allow to jump
	if (player_tile_collision)
	{
		if (sf::Keyboard::isKeyPressed(crouch_key))
		{
			player_tile_row = 6;

			player_height = player_height / 2;
			hitbox_y = player_height;

			// When player collides with ground, set y vel to zero
			if (player_tile_collision)
			{
				velocity.y = 0;
				// Change hitbox size when crouching
			}
		}
	}
}

void Player::knockoutAnimation(int& player_tile_row, int& player_health)
{
	if (player_health == 0)
	{
		player_tile_row = 4;
	}

	// Get the current frame of tileset
	player_uv_rect.left = current_image.x * player_uv_rect.width;
	player_uv_rect.top = current_image.y * player_uv_rect.height;
}

void Player::knockbackAnimation(bool& player_hit_status, int& player_tile_row, int player_direction)
{
	if (player_hit_status)
	{
		player_tile_row = 5;

		if (player_direction == 1)
		{
			player.setPosition(player.getPosition().x + 5, player.getPosition().y - 10);
		}
		else
		{
			player.setPosition(player.getPosition().x - 5, player.getPosition().y - 10);
		}
		player_hit_status = false;
	}
}

void Player::animatePlayer(int row, float& dt)
{
	current_image.y = row;
	total_time += dt;

	// Loop through tileset row
	if (total_time >= switch_time)
	{
		total_time -= switch_time;
		current_image.x++;
		if (current_image.x >= image_count.x)
		{
			current_image.x = 0;
		}
	}

	player.setTextureRect(player_uv_rect);
}

float Player::returnX()
{
	return player.getPosition().x;
}

float Player::returnY()
{
	return player.getPosition().y;
}

int Player::returnScale()
{
	return player.getScale().x;
}