#include "player1.hpp"

Player1::Player1(std::string player1_tileset, float player1_width, float& player1_height, float player1_x, float player1_y)
{
	player1.setOrigin(player1_width / 2, player1_height / 2);
	player1.setPosition(sf::Vector2f(player1_x, player1_y));

	// Load texture from file
	if (!player1_texture.loadFromFile(player1_tileset))
	{
		std::cout << "ERROR:: Cannot load player1 tileset from file" << "\n";
	}

	// Start at beginning of tileset
	total_time = 0.0f;
	current_image.x = 0;

	// Get size of individual tile
	player1_uv_rect.width = player1_texture.getSize().x / float(image_count.x);
	player1_uv_rect.height = (player1_height) / float(image_count.y);
}

void Player1::drawTo(sf::RenderWindow& window)
{
	window.draw(player1);
	player1.setTexture(player1_texture, true);

	std::cout << player1.getPosition().y << "\n";
}

void Player1::movePlayer(int player1_speed, bool& player1_tile_collision, float& dt, int& player1_tile_row, int& player1_health)
{
	velocity.x = 0;
	player1_tile_row = 0;

	// If player1 is colliding with tile set y vel to zero
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && player1_health > 0)
	{
		if (player1_tile_collision)
		{
			velocity.y = 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				velocity.y -= jump_power;
			}
		}
		else
		{
			velocity.y += gravity;
		}

		// If D is pressed move right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			velocity.x = player1_speed;
			player1_tile_row = 1;
			player1.setScale(1, 1);
		}

		// If A is pressed move left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			velocity.x = -player1_speed;
			player1_tile_row = 1;
			player1.setScale(-1, 1);
		}
	}

	player1.move(velocity * dt);
}

void Player1::collision(float screen_width, float player1_width, float player1_height, float& hitbox_x, float& hitbox_y)
{
	// Get sides of player1
	player1_top = player1.getPosition().y;
	player1_bottom = player1.getPosition().y + player1_height / 2;
	player1_left = player1.getPosition().x;
	player1_right = player1.getPosition().x + player1_width / 2;

	player1.setHitbox({ hitbox_x, hitbox_y, player1_width, player1_height });

	//  If player1 goes beyond screen borders, set player1 position
	// to just before screen border
	if (player1_right > screen_width)
	{
		player1.setPosition(screen_width - player1_width / 2, player1.getPosition().y);
	}
	else if (player1_left < player1_width / 2)
	{
		player1.setPosition(player1_width / 2, player1.getPosition().y);
	}
}

void Player1::attack(int& player1_tile_row, int& weak_reload_timer, int& strong_reload_timer, bool& weak_attack, bool& strong_attack)
{
	// If reload timer equals zero, allow attack
	if (weak_reload_timer == 0)
	{
		if (strong_attack == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				weak_reload_timer += 30;
				play_weak = 20;
				weak_attack = true;
			}
		}
	}
	else if (play_weak >= 0)
	{
		play_weak--;
		player1_tile_row = 3;
	}
	else
	{
		weak_reload_timer--;
		weak_attack = false;
	}

	// If strong attack reload timer equals zero, allow attack
	if (strong_reload_timer == 0)
	{
		if (weak_attack == false)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				strong_reload_timer += 100;
				play_strong = 20;
				strong_attack = true;
			}
	}
	else if (play_strong > 0)
	{
		play_strong--;
		player1_tile_row = 2;
	}
	else
	{
		strong_reload_timer--;
	}

}

void Player1::crouchAnimation(int& player1_tile_row, bool& player1_tile_collision, float& hitbox_y, float& player1_height)
{
	player1_height = 96;
	hitbox_y = 0;
	// When left shift is pressed crouch and don't allow to jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		player1_tile_row = 6;
		velocity.y += gravity;

		player1_height = player1_height / 2;
		hitbox_y = player1_height;

		// When player1 collides with ground, set y vel to zero
		if (player1_tile_collision)
		{
			velocity.y = 0;
			// Change hitbox size when crouching
		}
	}
	std::cout << player1_height << "\n";
}

void Player1::knockoutAnimation(int& player1_tile_row, int& player1_health)
{
	if (player1_health == 0)
	{
		player1_tile_row = 4;
	}
}

void Player1::animatePlayer(int row, float& dt)
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

	// Get the current frame of tileset
	player1_uv_rect.left = current_image.x * player1_uv_rect.width;
	player1_uv_rect.top = current_image.y * player1_uv_rect.height;

	player1.setTextureRect(player1_uv_rect);
}

float Player1::returnX()
{
	return player1.getPosition().x;
}

float Player1::returnY()
{
	return player1.getPosition().y;
}

int Player1::returnScale()
{
	return player1.getScale().x;
}