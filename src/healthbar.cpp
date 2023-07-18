#include <SFML/Graphics.hpp>
#include <healthbar.hpp>

Healthbar::Healthbar(std::string healthbar_texture_string, float healthbar_x, float healthbar_y)
{
	healthbar.setPosition(sf::Vector2f(healthbar_x, healthbar_y));

	if (healthbar_texture.loadFromFile(healthbar_texture_string))
	{
		std::cout << "ERROR:: cannot load healthbar texture from file"
				  << "\n";
	}
}

void Healthbar::changeHealthbarTexture(int row, int& player_health)
{
	current_image.y = row;
	current_image.x = player_health;

	healthbar_uv_rect.left = current_image.x * healthbar_uv_rect.width;
	healthbar_uv_rect.top = current_image.y * healthbar_uv_rect.height;

	healthbar.setTextureRect(healthbar_uv_rect);
}