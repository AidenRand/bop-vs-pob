#include "maintheme.hpp"

Maintheme::Maintheme(std::string main_theme_song_file)
{
	if (!main_theme_song_buffer.loadFromFile(main_theme_song_file))
	{
		std::cout << "ERROR:: Cannot load main theme song from file" << "\n";
	}
}

void Maintheme::playMainTheme()
{
	main_theme_song.setBuffer(main_theme_song_buffer);
	main_theme_song.play();
	main_theme_song.setLoop(true);
}

void Maintheme::setMainThemeVolume(int& main_theme_volume)
{
	main_theme_song.setVolume(main_theme_volume);
}