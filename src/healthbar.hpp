#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP

class Healthbar
{
public:
	Healthbar(std::string healthbar_texture_string);
	void createHealthbar(float healthbar_x, float healthbar_y);
	void changeHealthbarTexture(int row, int& player_health);
	void drawTo(sf::RenderWindow& window);

private:
	sf::Sprite healthbar;
	sf::Texture healthbar_texture;
	sf::IntRect healthbar_uv_rect;
	float total_time;
	sf::Vector2u image_count = sf::Vector2u(8, 1);
	sf::Vector2u current_image;
};

#endif