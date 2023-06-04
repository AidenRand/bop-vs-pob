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

private:
	int selectedItemIndex;
	sf::Text menu_text[MAX_NUMBER_OF_ITEMS];
	sf::Font font;
};

#endif