#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

class Background
{
public:
	Background();
	void setPos(float background_x, float background_y, float screen_width);
	void drawTo(sf::RenderWindow& window);
	void moveTiles();
	float returnX();
	sf::Sprite background;

private:
	sf::Texture background_texture;
};

#endif