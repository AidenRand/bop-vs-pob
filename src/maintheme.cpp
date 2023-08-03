#include "maintheme.hpp"

sf::SoundBuffer main_theme_song_buffer;
sf::Sound main_theme_song;

void playMainTheme(std::string main_theme_song_file)
{
	if (!main_theme_song_buffer.loadFromFile(main_theme_song_file))
	{
		std::cout << "ERROR:: Cannot load main theme song from file" << "\n";
	}

	main_theme_song.setBuffer(main_theme_song_buffer);
}