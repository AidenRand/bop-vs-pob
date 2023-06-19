#include "players.hpp"

Players::Players(float player_width, float player_height, float player_x, float player_y)
{
	std::cout << player_width << player_height;
	player.setOrigin(player_width / 2, player_height / 2);
	player.setPosition(sf::Vector2f(player_x, player_y));

	if (!bop_texture.loadFromFile("content/bop-tilesheet.png"))
	{
		std::cout << "ERROR:: Cannot load bop tileset from file" << "\n";
	}

	total_time = 0.0f;
	current_image.x = 0;

	bop_uv_rect.width = bop_texture.getSize().x / float(image_count.x);
	bop_uv_rect.height = (96) / float(image_count.y);
	player.setTexture(bop_texture, true);
}

void Players::drawTo(sf::RenderWindow& window)
{
	window.draw(player);
}

void Players::movePlayers(int player_speed, bool& player_tile_collision, float& dt, int& player_tile_row)
{
	velocity.x = 0;
	player_tile_row = 0;

	// If player is colliding with tile set gravity to zero
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = player_speed;
		player_tile_row = 1;
		player.setScale(1, 1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = -player_speed;
		player_tile_row = 1;
		player.setScale(-1, 1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		player_tile_row = 6;
	}

	player.move(velocity * dt);
}

void Players::collision(float screen_width, int player_width, int player_height)
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

void Players::attack(int& player_tile_row)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		player_tile_row = 3;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		player_tile_row = 4;
	}
}

void Players::animateBop(int row, float& dt)
{
	current_image.y = row;
	total_time += dt;

	if (total_time >= switch_time)
	{
		total_time -= switch_time;
		current_image.x++;
		if (current_image.x >= image_count.x)
		{
			current_image.x = 0;
		}
	}

	bop_uv_rect.left = current_image.x * bop_uv_rect.width;
	bop_uv_rect.top = current_image.y * bop_uv_rect.height;

	player.setTextureRect(bop_uv_rect);
}