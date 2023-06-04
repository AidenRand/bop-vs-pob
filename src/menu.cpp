#include "menu.hpp"

Menu::Menu(float screen_width, float screen_height)
{
	if (!font.loadFromFile("content/pixelfaceonfire.ttf"))
	{
		std::cout << "ERROR:: Cannot load menu font from file" << "\n";
	}

	// Set menu text variables
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		menu_text[i].setFont(font);
		menu_text[i].setCharacterSize(20);
		menu_text[i].setFillColor(sf::Color(181, 35, 35));
	}

	menu_text[0].setString("PLAY");
	menu_text[0].setPosition(sf::Vector2f(screen_width / 2.2, screen_height / (MAX_NUMBER_OF_ITEMS + 1.5) * 2));
	menu_text[0].setFillColor(sf::Color(134, 16, 16));

	menu_text[1].setString("QUIT");
	menu_text[1].setPosition(sf::Vector2f(screen_width / 2.2, screen_height / (MAX_NUMBER_OF_ITEMS + 2) * 3));

	selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu_text[i]);
	}
}

void Menu::moveUp()
{
	// Move menu select up if item index is greater than zero
	if (selectedItemIndex - 1 >= 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			menu_text[selectedItemIndex].setFillColor(sf::Color(181, 35, 35));
			selectedItemIndex--;
			menu_text[selectedItemIndex].setFillColor(sf::Color(134, 16, 16));
		}
	}
}

void Menu::moveDown()
{
	// Move menu select down if item index is less than max index size
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			menu_text[selectedItemIndex].setFillColor(sf::Color(181, 35, 35));
			selectedItemIndex++;
			menu_text[selectedItemIndex].setFillColor(sf::Color(134, 16, 16));
		}
	}
}