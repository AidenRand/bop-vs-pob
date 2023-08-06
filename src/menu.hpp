#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu();
	~Menu();

	void createButtons(float screen_width, float screen_height, int font_size);
	void drawButtons(sf::RenderWindow& window);
	void fetchMenuSounds(std::string& nav_menu_sound_file, std::string& sel_menu_sound_file);
	void navigateMenu(sf::Keyboard::Key key, bool checkpressed);
	void playGame(bool& game_running);
	void closeGame(sf::RenderWindow& window);
	void createControls(std::string controls_screen_file, float controls_screen_x, float controls_screen_y, bool& controls_showing);
	void drawControls(sf::RenderWindow& window, bool& controls_showing);
	void createTitle(float title_x, float title_y);
	void animateTitle(int row, float dt);
	void drawTitle(sf::RenderWindow& window);
	void backToMenu(bool& game_running, bool& controls_showing);

private:
	int selectedItemIndex = 0;
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

	sf::Sprite controls_screen;
	sf::Texture controls_screen_texture;

	sf::SoundBuffer nav_menu_sound_buffer;
	sf::Sound nav_menu_sound;

	sf::SoundBuffer sel_menu_sound_buffer;
	sf::Sound sel_menu_sound;

	sf::SoundBuffer main_theme_buffer;
	sf::Sound main_theme;
};

#endif