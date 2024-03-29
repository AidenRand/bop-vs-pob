#include "game.hpp"
#include "clouds.hpp"
#include "endgame.hpp"
#include "foreground.hpp"
#include "healthbar.hpp"
#include "maintheme.hpp"
#include "menu.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "world.hpp"
#include <SFML/Graphics.hpp>

void game(sf::RenderWindow& window, float& screen_width, float& screen_height)
{
	bool game_running = false;
	bool controls_showing = false;

	// Create clouds texture
	Clouds cloud_tile;
	Clouds cloud_tile2;
	std::vector<Clouds> cloud_vector;
	long unsigned int max_cloud_tiles = 2;
	int cloud_scroll_speed = 20;
	float clouds_x = 0;
	float clouds_y = -100;
	cloud_tile.setPos(clouds_x, clouds_y);
	cloud_tile2.setPos(clouds_x - screen_width, clouds_y);

	// create background
	sf::Sprite background;
	sf::Texture background_texture;
	if (!background_texture.loadFromFile("content/bop-vs-pob-bckgr.png"))
	{
		std::cout << "ERROR::Could not load background from file"
				  << "\n";
	}
	background.setTexture(background_texture);

	// Create left foregound
	float left_foreground_x = 0;
	float left_foreground_y = 412;
	std::string left_foreground_texture = "content/left-foreground.png";
	Foreground left_foreground(left_foreground_texture, left_foreground_x, left_foreground_y);

	// Create right foreground
	std::string right_foreground_texture = "content/right-foreground.png";
	float right_foreground_x = 704;
	float right_foreground_y = 412;
	Foreground right_foreground(right_foreground_texture, right_foreground_x, right_foreground_y);

	// Main theme song variables
	std::string main_theme_song_file = "sounds/main_theme.wav";
	int main_theme_volume = 2;
	Maintheme main_theme(main_theme_song_file);
	main_theme.playMainTheme();

	// Create menu
	Menu menu;
	int menu_font_size = 30;
	float title_x = 230;
	float title_y = -130;
	menu.createButtons(screen_width, screen_height, menu_font_size);
	menu.createTitle(title_x, title_y);

	// Menu sounds
	std::string nav_menu_sound_file = "sounds/Menu Selection Click.wav";
	std::string sel_menu_sound_file = "sounds/vgmenuhighlight.wav";
	menu.fetchMenuSounds(nav_menu_sound_file, sel_menu_sound_file);

	// Controls screen variables
	std::string controls_texture_file = "content/bop-vs-pob-controls.png";
	float controls_screen_x = 0;
	float controls_screen_y = 0;

	// Create player 1 healthbar
	float p1_healthbar_x = 30;
	float p1_healthbar_y = 20;
	std::string p1_healthbar_texture = "content/bop-healthbar-tileset.png";
	Healthbar p1_healthbar(p1_healthbar_texture);

	// Create player 2 healthbar
	float p2_healthbar_x = 620;
	float p2_healthbar_y = 20;
	std::string p2_healthbar_texture = "content/pob-healthbar-spritesheet.png";
	Healthbar p2_healthbar(p2_healthbar_texture);

	// Endgame text variables
	sf::Keyboard::Key reset_game_button = sf::Keyboard::Key::Space;
	float endgame_text_x = 240;
	float endgame_text_y = 150;

	// Player 1 won endgame text
	std::string p1_endgame_text_file = "content/bop-endgame-text.png";
	Endgame p1_endgame(p1_endgame_text_file, endgame_text_x, endgame_text_y);

	// Player 2 won endgame text
	std::string p2_endgame_text_file = "content/pob-endgame-text.png";
	Endgame p2_endgame(p2_endgame_text_file, endgame_text_x, endgame_text_y);

	// Universal player variables
	int player_speed = 400;
	std::string strong_attack_collision_sound = "sounds/Meow.wav";
	std::string weak_attack_collision_sound = "sounds/weak-attack.wav";
	std::string knockout_sound = "sounds/cat_purrsleepy_loop.wav";
	int strong_attack_volume = 2;
	int weak_attack_volume = 2;
	int knockout_sound_volume = 10;

	// Create player one
	float p1_x = 150;
	float p1_y = 300;
	int p1_tile_row = 0;
	bool p1_weak_attack = false;
	bool p1_strong_attack = false;
	bool p1_hit_status = false;
	int p1_health = 10;
	float player1_width = 96;
	float player1_height = 96;
	float hitbox1_x = 0;
	float hitbox1_y = 0;
	float hitbox1_width = 100;
	int p1_weak_reload_timer = 0;
	int p1_strong_reload_timer = 0;
	std::string bop_tileset = "content/bop-tilesheet.png";

	sf::Keyboard::Key p1_jump_key = sf::Keyboard::Key::W;
	sf::Keyboard::Key p1_crouch_key = sf::Keyboard::Key::S;
	sf::Keyboard::Key p1_move_left_key = sf::Keyboard::Key::A;
	sf::Keyboard::Key p1_move_right_key = sf::Keyboard::Key::D;

	sf::Keyboard::Key p1_weak_attack_key = sf::Keyboard::Key::F;
	sf::Keyboard::Key p1_strong_attack_key = sf::Keyboard::Key::E;

	// Create player 1 projectile
	bool p1_proj_dead = false;
	std::string p1_proj_texture_file = "content/bop-poop.png";
	std::vector<Projectile> p1_proj_vector;

	Player player_1(player1_height, player1_width, p1_x, p1_y, 1);
	player_1.fetchTexture(bop_tileset, player1_height);
	player_1.fetchSounds(strong_attack_collision_sound, weak_attack_collision_sound, knockout_sound);
	player_1.setSoundVolume(strong_attack_volume, weak_attack_volume, knockout_sound_volume);

	// Create player two
	float p2_x = 800;
	float p2_y = 300;
	int p2_tile_row = 0;
	bool p2_weak_attack = false;
	bool p2_strong_attack = false;
	bool p2_hit_status = false;
	int p2_health = 10;
	int p2_weak_reload_timer = 0;
	int p2_strong_reload_timer = 0;
	float player2_width = 96;
	float player2_height = 96;
	float hitbox2_x = 0;
	float hitbox2_y = 0;
	float hitbox2_width = 100;
	std::string pob_tileset = "content/pob-tilesheet.png";

	Player player_2(player2_height, player2_width, p2_x, p2_y, 2);
	player_2.fetchTexture(pob_tileset, player2_height);
	player_2.fetchSounds(strong_attack_collision_sound, weak_attack_collision_sound, knockout_sound);
	player_2.setSoundVolume(strong_attack_volume, weak_attack_volume, knockout_sound_volume);

	// Player 2 movement keys
	sf::Keyboard::Key p2_jump_key = sf::Keyboard::Key::P;
	sf::Keyboard::Key p2_crouch_key = sf::Keyboard::Key::SemiColon;
	sf::Keyboard::Key p2_move_left_key = sf::Keyboard::Key::L;
	sf::Keyboard::Key p2_move_right_key = sf::Keyboard::Key::Quote;

	// Player 2 attack keys
	sf::Keyboard::Key p2_weak_attack_key = sf::Keyboard::Key::K;
	sf::Keyboard::Key p2_strong_attack_key = sf::Keyboard::Key::O;

	// Create player 2 projectile
	bool p2_proj_dead = false;
	std::string p2_proj_texture_file = "content/pob-puke.png";
	std::vector<Projectile> p2_proj_vector;

	// Create map
	const int map_height = 17;
	const int map_width = 30;
	int tile_width = 32;
	int tile_height = 32;

	World world_map;
	sf::String tile_map[map_height] = {
		"                                     ",
		"                                     ",
		"                                     ",
		"                                     ",
		"                                     ",
		"                                     ",
		"                                     ",
		"                                     ",
		"                                     ",
		"                                     ",
		"                                     ",
		"                                     ",
		"                                     ",
		"                                     ",
		"                                     ",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	};

	// Make delta time
	float dt;
	sf::Clock clock;

	while (window.isOpen())
	{
		// Get delta time
		dt = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (!game_running)
			{
				if (event.type == sf::Event::KeyPressed)
				{
					menu.navigateMenu(event.key.code, true);
				}

				if (event.type == sf::Event::KeyReleased)
				{
					menu.navigateMenu(event.key.code, false);
				}
			}
		}

		window.clear();
		window.draw(background);

		main_theme.setMainThemeVolume(main_theme_volume);

		// Draw moving clouds
		if (cloud_vector.size() < max_cloud_tiles)
		{
			cloud_vector.push_back(cloud_tile);
		}

		if (cloud_tile.returnX() > screen_width)
		{
			cloud_tile.setPos(clouds_x - screen_width, clouds_y);
			cloud_tile.moveTiles(cloud_scroll_speed, dt);
		}

		if (cloud_tile2.returnX() > screen_width)
		{
			cloud_tile2.setPos(clouds_x - screen_width, clouds_y);
			cloud_tile2.moveTiles(cloud_scroll_speed, dt);
		}

		cloud_tile.moveTiles(cloud_scroll_speed, dt);
		cloud_tile2.moveTiles(cloud_scroll_speed, dt);
		cloud_tile.drawTo(window);
		cloud_tile2.drawTo(window);

		// Draw game menu
		menu.drawControls(window, controls_showing);
		menu.backToMenu(game_running, controls_showing);
		if (!controls_showing)
		{
			if (!game_running)
			{
				main_theme_volume = 5;

				menu.drawButtons(window);
				menu.closeGame(window);
				menu.playGame(game_running);
				menu.createControls(controls_texture_file, controls_screen_x, controls_screen_y, controls_showing);
				menu.createTitle(title_x, title_y);
				menu.animateTitle(0, dt);
				menu.drawTitle(window);
			}
			else
			{
				main_theme_volume = 1;

				bool p1_tile_collision = false;
				bool p2_tile_collision = false;

				// Draw player 1 healthbar
				p1_healthbar.createHealthbar(p1_healthbar_x, p1_healthbar_y);
				p1_healthbar.changeHealthbarTexture(0, p1_health);
				p1_healthbar.drawTo(window);

				// Draw player 2 healthbar
				p2_healthbar.createHealthbar(p2_healthbar_x, p2_healthbar_y);
				p2_healthbar.changeHealthbarTexture(0, p2_health);
				p2_healthbar.drawTo(window);

				// Draw player 1 wins endgame text
				p1_endgame.drawTo(window, p2_health);

				// Draw player 2 wins endame text
				p2_endgame.drawTo(window, p1_health);

				// If p1 or p2 health equals zero, allow game to be reset
				if (p1_health == 0 || p2_health == 0)
				{
					p1_endgame.resetGame(reset_game_button, player_1, p1_health, p1_x, p1_y);
					p2_endgame.resetGame(reset_game_button, player_2, p2_health, p2_x, p2_y);
				}

				// Draw tile map if game is running
				world_map.createMap(tile_map, map_width, map_height, tile_width, tile_height, window, player_1, player_2, p1_tile_collision, p2_tile_collision, player1_width, player2_width);

				// Draw player 1 projectile
				Projectile p1_proj(p1_proj_texture_file);
				if (p1_strong_attack)
				{
					p1_proj.spawnProj(player_1.returnScale());
					p1_proj.setPos(player_1.returnX(), player_1.returnY());
					p1_strong_attack = false;
					p1_proj_vector.push_back(p1_proj);
				}

				for (long unsigned int i = 0; i < p1_proj_vector.size(); i++)
				{
					p1_proj_vector[i].fireProj();
					p1_proj_vector[i].drawTo(window);
					p1_proj_vector[i].killProj(p1_proj_dead, screen_width);

					if (p1_proj_dead)
					{
						p1_proj_vector.erase(p1_proj_vector.begin() + i);
						p1_proj_dead = false;
					}
				}

				// Draw player 2 projectile
				Projectile p2_proj(p2_proj_texture_file);
				if (p2_strong_attack)
				{
					p2_proj.spawnProj(player_2.returnScale());
					p2_proj.setPos(player_2.returnX(), player_2.returnY());
					p2_strong_attack = false;
					p2_proj_vector.push_back(p2_proj);
				}

				for (long unsigned int i = 0; i < p2_proj_vector.size(); i++)
				{
					p2_proj_vector[i].fireProj();
					p2_proj_vector[i].drawTo(window);
					p2_proj_vector[i].killProj(p2_proj_dead, screen_width);

					if (p2_proj_dead)
					{
						p2_proj_vector.erase(p2_proj_vector.begin() + i);
						p2_proj_dead = false;
					}
				}

				// Draw player 1
				player_1.drawTo(window);
				player_1.movePlayer(player_speed, p1_tile_collision, dt, p1_tile_row, p1_health, p1_move_left_key, p1_move_right_key, p1_jump_key, p1_crouch_key);
				player_1.weakAttackCollision(player_2, p1_weak_attack, p2_hit_status, p2_health);
				player_1.strongAttackCollision(player_2, p1_weak_attack, p1_proj_vector, p1_proj_dead, p2_health);
				player_1.knockbackAnimation(p1_hit_status, p1_tile_row, player_2.returnScale(), p2_health);
				player_1.collision(screen_width, player1_width, player1_height, hitbox1_x, hitbox1_y, hitbox1_width);
				player_1.attack(p1_tile_row, p1_weak_reload_timer, p1_strong_reload_timer, p1_weak_attack, p1_strong_attack, p1_weak_attack_key, p1_strong_attack_key, p1_health, p2_health);
				player_1.crouchAnimation(p1_tile_row, p1_tile_collision, hitbox1_y, player1_height, p1_crouch_key);
				player_1.knockoutAnimation(p1_tile_row, p1_health, p1_tile_collision);
				player_1.animatePlayer(p1_tile_row, dt);
				player_1.playerPlayerCollision(player_2, p1_move_left_key, p1_move_right_key, player2_width);

				// Draw player 2
				player_2.drawTo(window);
				player_2.movePlayer(player_speed, p2_tile_collision, dt, p2_tile_row, p2_health, p2_move_left_key, p2_move_right_key, p2_jump_key, p2_crouch_key);
				player_2.weakAttackCollision(player_1, p2_weak_attack, p1_hit_status, p1_health);
				player_2.strongAttackCollision(player_1, p1_hit_status, p2_proj_vector, p2_proj_dead, p1_health);
				player_2.knockbackAnimation(p2_hit_status, p2_tile_row, player_1.returnScale(), p1_health);
				player_2.collision(screen_width, player2_width, player2_height, hitbox2_x, hitbox2_y, hitbox2_width);
				player_2.attack(p2_tile_row, p2_weak_reload_timer, p2_strong_reload_timer, p2_weak_attack, p2_strong_attack, p2_weak_attack_key, p2_strong_attack_key, p2_health, p1_health);
				player_2.crouchAnimation(p2_tile_row, p2_tile_collision, hitbox2_y, player2_height, p2_crouch_key);
				player_2.knockoutAnimation(p2_tile_row, p2_health, p2_tile_collision);
				player_2.animatePlayer(p2_tile_row, dt);
				player_2.playerPlayerCollision(player_1, p2_move_left_key, p2_move_right_key, player1_width);

				// Draw foreground
				left_foreground.drawTo(window);
				right_foreground.drawTo(window);
			}
		}

		window.display();
	}
}