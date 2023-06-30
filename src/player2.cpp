#include "player2.hpp"

Player2::Player2(std::string p2_tileset, float p2_width, float p2_height, float p2_x, float p2_y)
{
	player2.setOrigin(p2_width / 2, p2_height / 2);
	player2.setPosition(sf::Vector2f(p2_x, p2_y));

	if (!p2_texture.loadFromFile(p2_tileset))
	{
		std::cout << "ERROR:: Cannot load tileset from file" << "\n";
	}

	// Start at beginning of tileset
	total_time = 0.0f;
	current_image.x = 0;

	// Get size of individual tile
	p2_uv_rect.width = p2_texture.getSize().x / float(image_count.x);
	p2_uv_rect.height = (p2_height) / float(image_count.y);
}

void Player2::drawTo(sf::RenderWindow& window)
{
	window.draw(player2);
	player2.setTexture(p2_texture, true);
}

void Player2::animatePlayer(int row, float& dt)
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

	p2_uv_rect.left = current_image.x * p2_uv_rect.width;
	p2_uv_rect.top = current_image.y * p2_uv_rect.height;

	player2.setTextureRect(p2_uv_rect);
}