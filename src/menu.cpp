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


	if (!title_texture.loadFromFile("content/bop-vs-pob-title.png"))
	{
		std::cout << "ERROR::Cannot load title texture from file" << "\n";
	}
	total_time = 0.0f;
	current_image.x = 0;
	title_uv_rect.width = title_texture.getSize().x / float(image_count.x);
	title_uv_rect.height = title_texture.getSize().y / float(image_count.y);
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
	// Move menu select down if item index is less than max index size
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			menu_text[selectedItemIndex].setFillColor(sf::Color(181, 35, 35));
			selectedItemIndex++;
			menu_text[selectedItemIndex].setFillColor(sf::Color(134, 16, 16));
		}
	}
}

void Menu::moveDown()
{
	// Move menu select up if item index is greater than zero
	if (selectedItemIndex - 1 >= 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			menu_text[selectedItemIndex].setFillColor(sf::Color(181, 35, 35));
			selectedItemIndex--;
			menu_text[selectedItemIndex].setFillColor(sf::Color(134, 16, 16));
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
	std::cout << game_running;
}

void Menu::createTitle(float title_x, float title_y)
{
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