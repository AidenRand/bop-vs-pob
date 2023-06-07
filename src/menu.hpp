#ifndef MENU_HPP
#define MENU_HPP

#define MAX_NUMBER_OF_ITEMS 2

class Menu
{
public:
	Menu();
	~Menu();

	void createButtons(float screen_width, float screen_height, int font_size);
	void drawButtons(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void closeGame(sf::RenderWindow& window);
	void playGame(bool& game_running);
	void createTitle(float title_x, float title_y);
	void animateTitle(int row, float dt);
	void drawTitle(sf::RenderWindow& window);
	void backToMenu(bool& game_running);

private:
	int selectedItemIndex;
	sf::Text menu_text[MAX_NUMBER_OF_ITEMS];
	sf::Font font;

	bool move_up = false;
	bool move_down = false;

	sf::Sprite title;
	sf::Texture title_texture;
	sf::IntRect title_uv_rect;
	float total_time;
	float switch_time = 0.1f;
	sf::Vector2u image_count = sf::Vector2u(8, 1);
	sf::Vector2u current_image;
};

#endif