#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

class Background
{
public:
	Background(float background_x, float background_y, float screen_width, float screen_height);

private:
	sf::Sprite background;
	sf::Texture background_texture;
};

#endif