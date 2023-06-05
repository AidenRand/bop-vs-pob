#ifndef MENU_HPP
#define MENU_HPP

#define MAX_NUMBER_OF_ITEMS 2

class Menu
{
public:
	Menu(float screen_height, float screen_width);
	~Menu();

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void closeGame(sf::RenderWindow& window);
	void playGame(bool& game_running);
	void animateTitle(int row, float dt);

private:
	int selectedItemIndex;
	sf::Text menu_text[MAX_NUMBER_OF_ITEMS];
	sf::Font font;

	bool move_up = false;
	bool move_down = false;

	sf::IntRect title_uv_rect;
	float total_time;
	float switch_time = 0.5f;
	sf::Vector2u image_count = sf::Vector2u(8, 1);
	sf::Vector2u current_image;
};

#endif