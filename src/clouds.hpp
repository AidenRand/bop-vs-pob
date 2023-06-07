#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

class Clouds
{
public:
	Clouds();
	void setPos(float background_x, float background_y);
	void drawTo(sf::RenderWindow& window);
	void moveTiles(int back_scroll_speed, float& dt);
	float returnX();

private:
	sf::Sprite back_clouds;
	sf::Texture back_clouds_texture;
};

#endif