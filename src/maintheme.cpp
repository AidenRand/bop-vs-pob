#include "maintheme.hpp"

Maintheme::Maintheme(std::string main_theme_song_file)
{
	if (!main_theme_song_buffer.loadFromFile(main_theme_song_file))
	{
		std::cout << "ERROR:: Cannot load main theme song from file" << "\n";
	}

	main_theme_song.setBuffer(main_theme_song_buffer);
}

void Maintheme::playMainTheme(int& main_theme_volume)
{
	main_theme_song.setVolume(main_theme_volume);
	main_theme_song.setLoop(true);
	main_theme_song.play();
}


