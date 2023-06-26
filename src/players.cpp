#include "players.hpp"

Players::Players(std::string player_tileset, float player_width, float& player_height, float player_x, float player_y)
{
	player.setOrigin(player_width / 2, player_height / 2);
	player.setPosition(sf::Vector2f(player_x, player_y));
	player.setHitbox({ 0, 0, player_width, player_height });

	// Load texture from file
	if (!player_texture.loadFromFile(player_tileset))
	{
		std::cout << "ERROR:: Cannot load player tileset from file" << "\n";
	}

	// Start at beginning of tileset
	total_time = 0.0f;
	current_image.x = 0;

	// Get size of individual tile
	player_uv_rect.width = player_texture.getSize().x / float(image_count.x);
	player_uv_rect.height = (player_height) / float(image_count.y);
}

void Players::drawTo(sf::RenderWindow& window)
{
	window.draw(player);
	player.setTexture(player_texture, true);

	std::cout << player.getPosition().y << "\n";
}

void Players::movePlayers(int player_speed, bool& player_tile_collision, float& dt, int& player_tile_row, int& player_health)
{
	velocity.x = 0;
	player_tile_row = 0;

	// If player is colliding with tile set y vel to zero
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && player_health > 0)
	{
		if (player_tile_collision)
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
			velocity.x = player_speed;
			player_tile_row = 1;
			player.setScale(1, 1);
		}

		// If A is pressed move left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			velocity.x = -player_speed;
			player_tile_row = 1;
			player.setScale(-1, 1);
		}
	}

	player.move(velocity * dt);
}

void Players::collision(float screen_width, float player_width, float player_height)
{
	// Get sides of player
	player_top = player.getPosition().y;
	player_bottom = player.getPosition().y + player_height / 2;
	player_left = player.getPosition().x;
	player_right = player.getPosition().x + player_width / 2;

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

void Players::attack(int& player_tile_row, int& weak_reload_timer, int& strong_reload_timer, bool& weak_attack, bool& strong_attack)
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
		player_tile_row = 3;
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
		player_tile_row = 2;
	}
	else
	{
		strong_reload_timer--;
		strong_attack = false;
	}

}

void Players::crouchAnimation(int& player_tile_row, bool& player_tile_collision)
{
	// When left shift is pressed crouch and don't allow to jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		player_tile_row = 6;
		velocity.y += gravity;

		// When player collides with ground, set y vel to zero
		if (player_tile_collision)
		{
			velocity.y = 0;
		}
	}
}

void Players::knockoutAnimation(int& player_tile_row, int& player_health)
{
	if (player_health == 0)
	{
		player_tile_row = 4;
	}
}

void Players::animatePlayer(int row, float& dt)
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
	player_uv_rect.left = current_image.x * player_uv_rect.width;
	player_uv_rect.top = current_image.y * player_uv_rect.height;

	player.setTextureRect(player_uv_rect);
}