#include "players.hpp"

Players::Players(float player_width, float player_height, float player_x, float player_y)
{
	std::cout << player_width << player_height;
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

void Players::movePlayers(int player_speed, bool& player_tile_collision, float& dt)
{
	velocity.x = 0;

	// velocity.y += gravity;
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
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = -player_speed;
	}

	player.move(velocity * dt);
}

void Players::collision(float screen_width, int player_width)
{

	player_top = player.getPosition().y;
	player_bottom = player.getPosition().y + player_width;
	player_left = player.getPosition().x;
	player_right = player.getPosition().x + player.getTextureRect().width;

	//  If player goes beyond screen borders, set player position
	// to just before screen border
	if (player_right > screen_width - player_width)
	{
		player.setPosition(screen_width - player_width, player.getPosition().y);
	}
	else if (player_left < 0)
	{
		player.setPosition(0, player.getPosition().y);
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