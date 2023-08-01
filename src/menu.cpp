#include "menu.hpp"
#include <SFML/Graphics.hpp>

Menu::Menu()
{
	// Load font
	if (!font.loadFromFile("content/pixelfaceonfire.ttf"))
	{
		std::cout << "ERROR:: Cannot load menu font from file"
				  << "\n";
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
	menu_text[0].setFillColor(sf::Color(235, 0, 0));

	menu_text[1].setString("QUIT");
	menu_text[1].setPosition(sf::Vector2f(screen_width / 2.25, screen_height / (MAX_NUMBER_OF_ITEMS + 2) * 3));
	menu_text[1].setFillColor(sf::Color(255, 243, 0));

	menu_text[2].setString("CONTROLS");
	menu_text[2].setPosition(sf::Vector2f(screen_width / 2.6, screen_height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	menu_text[2].setFillColor(sf::Color(255, 243, 0));

	selectedItemIndex = 0;
}

void Menu::drawButtons(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu_text[i]);
	}
}

void Menu::fetchMenuSounds(std::string& nav_menu_sound_file, std::string& sel_menu_sound_file, std::string& main_theme_file, int& main_theme_volume)
{
	if (!nav_menu_sound_buffer.loadFromFile(nav_menu_sound_file))
	{
		std::cout << "ERROR:: Cannot load nav menu sound from file"
				  << "\n";
	}

	if (!sel_menu_sound_buffer.loadFromFile(sel_menu_sound_file))
	{
		std::cout << "ERROR:: Cannot load select menu sound from file"
				  << "\n";
	}

	if (!main_theme_buffer.loadFromFile(main_theme_file))
	{
		std::cout << "ERROR:: Cannot load main theme music from file"
				  << "\n";
	}

	main_theme.setBuffer(main_theme_buffer);
	main_theme.setVolume(main_theme_volume);

	nav_menu_sound.setBuffer(nav_menu_sound_buffer);
	sel_menu_sound.setBuffer(sel_menu_sound_buffer);

	nav_menu_sound.setVolume(2);
	sel_menu_sound.setVolume(20);

	nav_menu_sound.setPitch(2);
}

void Menu::playMainTheme(sf::RenderWindow& window)
{
	if (window.isOpen())
	{
		main_theme.play();
	}
}

void Menu::navigateMenu(sf::Keyboard::Key key, bool checkpressed)
{
	if (checkpressed)
	{
		if (key == sf::Keyboard::Down)
		{
			if (selectedItemIndex + 1 != MAX_NUMBER_OF_ITEMS)
			{
				menu_text[selectedItemIndex].setFillColor(sf::Color(255, 243, 0));
				selectedItemIndex += 1;
				nav_menu_sound.play();
				menu_text[selectedItemIndex].setFillColor(sf::Color(235, 0, 0));
			}
		}
		if (key == sf::Keyboard::Up)
		{
			if (selectedItemIndex > 0)
			{
				menu_text[selectedItemIndex].setFillColor(sf::Color(255, 243, 0));
				selectedItemIndex -= 1;
				nav_menu_sound.play();
				menu_text[selectedItemIndex].setFillColor(sf::Color(235, 0, 0));
			}
		}
	}
}

void Menu::closeGame(sf::RenderWindow& window)
{
	// If Quit is being hovered and enter is pressed, close window
	if (selectedItemIndex == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			window.close();
		}
	}
}

void Menu::playGame(bool& game_running)
{
	if (selectedItemIndex == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			game_running = true;
			sel_menu_sound.play();
		}
	}
}

void Menu::createControls(std::string controls_screen_file, float controls_screen_x, float controls_screen_y, bool& controls_showing)
{
	if (!controls_screen_texture.loadFromFile(controls_screen_file))
	{
		std::cout << "ERROR:: Could not load controls screen texture from file"
				  << "\n";
	}

	controls_screen.setTexture(controls_screen_texture);
	controls_screen.setPosition(sf::Vector2f(controls_screen_x, controls_screen_y));

	if (selectedItemIndex == 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		controls_showing = true;
		sel_menu_sound.play();
	}
}

void Menu::drawControls(sf::RenderWindow& window, bool& controls_showing)
{
	if (controls_showing)
	{
		window.draw(controls_screen);
	}
}

void Menu::createTitle(float title_x, float title_y)
{
	// Load title texture
	if (!title_texture.loadFromFile("content/bop-vs-pob-title.png"))
	{
		std::cout << "ERROR::Cannot load title texture from file"
				  << "\n";
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

void Menu::backToMenu(bool& game_running, bool& controls_showing)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		game_running = false;
		controls_showing = false;
	}
}