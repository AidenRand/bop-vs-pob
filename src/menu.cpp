#include "menu.hpp"
#include <SFML/Graphics.hpp>

Menu::Menu()
{
	// Load font
	if (!font.loadFromFile("content/pixelfaceonfire.ttf"))
	{
		std::cout << "ERROR:: Cannot load menu font from file" << "\n";
	}
}

Menu::~Menu()
{
}

void Menu::createButtons(float screen_width, float screen_height, int font_size)
{
	// Set menu text variables
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		menu_text[i].setFont(font);
		menu_text[i].setCharacterSize(font_size);
	}

	menu_text[0].setString("PLAY");
	menu_text[0].setPosition(sf::Vector2f(screen_width / 2.25, screen_height / (MAX_NUMBER_OF_ITEMS + 1.5) * 2));
	menu_text[0].setFillColor(sf::Color(255, 243, 0));

	menu_text[1].setString("QUIT");
	menu_text[1].setPosition(sf::Vector2f(screen_width / 2.25, screen_height / (MAX_NUMBER_OF_ITEMS + 2) * 3));
	menu_text[1].setFillColor(sf::Color(250, 0, 0));

	menu_text[2].setString("CONTROLS");
	menu_text[2].setPosition(sf::Vector2f(screen_width / 2.25, screen_height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	menu_text[2].setFillColor(sf::Color(250, 0, 0));
}

void Menu::drawButtons(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu_text[i]);
	}
}

void Menu::selectMenu()
{
	std::cout << selectedItemIndex << "\n";
	// Instead of directly moving down when the button is pressed
	// Make two bool values and set them to true if the button is pressed
	// and false otherwise. when it is true move but don't move when it is false
	// Move menu select up if item index is greater than zero
	if (selectedItemIndex < MAX_NUMBER_OF_ITEMS)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			menu_text[selectedItemIndex].setFillColor(sf::Color(235, 0, 0));
			selectedItemIndex++;
			menu_text[selectedItemIndex].setFillColor(sf::Color(255, 243, 0));
		}
	}
	if (selectedItemIndex > 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			menu_text[selectedItemIndex].setFillColor(sf::Color(235, 0, 0));
			selectedItemIndex--;
			menu_text[selectedItemIndex].setFillColor(sf::Color(255, 243, 0));
		}
	}
}

void Menu::closeGame(sf::RenderWindow& window)
{
	// If Quit is being hovered and enter is pressed, close window
	if (selectedItemIndex == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			window.close();
		}
	}
}

void Menu::playGame(bool& game_running)
{
	if (selectedItemIndex == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			game_running = true;
		}
	}
}

void Menu::createTitle(float title_x, float title_y)
{
	// Load title texture
	if (!title_texture.loadFromFile("content/bop-vs-pob-title.png"))
	{
		std::cout << "ERROR::Cannot load title texture from file" << "\n";
	}
	// Create title texture variables
	total_time = 0.0f;
	current_image.x = 0;
	title_uv_rect.width = title_texture.getSize().x / float(image_count.x);
	title_uv_rect.height = title_texture.getSize().y / float(image_count.y);
	title.setPosition(sf::Vector2f(title_x, title_y));
	title.setTexture(title_texture, true);
}

void Menu::animateTitle(int row, float dt)
{
	current_image.y = row;
	total_time += dt;

	// Loop through sprite sheet
	if (total_time >= switch_time)
	{
		total_time -= switch_time;
		current_image.x++;
		if (current_image.x >= image_count.x)
		{
			current_image.x = 0;
		}
	}

	// Set texture to current image
	title_uv_rect.left = current_image.x * title_uv_rect.width;
	title_uv_rect.top = current_image.y * title_uv_rect.height;

	title.setTextureRect(title_uv_rect);
}

void Menu::drawTitle(sf::RenderWindow& window)
{
	window.draw(title);
}

void Menu::backToMenu(bool& game_running)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		game_running = false;
	}
}