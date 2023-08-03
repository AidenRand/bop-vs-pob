#ifndef MAINTHEME_HPP
#define MAINTHEME_HPP

class Maintheme
{
public:
	Maintheme(std::string main_theme_song_file);
	void playMainTheme(int& main_theme_volume);

private:
	sf::SoundBuffer main_theme_song_buffer;
	sf::Sound main_theme_song;
};

#endif