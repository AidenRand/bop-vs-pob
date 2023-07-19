#include "game.hpp"
#include "clouds.hpp"
#include "foreground.hpp"
#include "healthbar.hpp"
#include "menu.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "world.hpp"
#include <SFML/Graphics.hpp>

void game(sf::RenderWindow& window, float& screen_width, float& screen_height)
{
	bool game_running = false;

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

	// Create menu
	Menu menu;
	int menu_font_size = 30;
	float title_x = 230;
	float title_y = -130;
	menu.createButtons(screen_width, screen_height, menu_font_size);
	menu.createTitle(title_x, title_y);

	// Create player 1 healthbar
	float p1_healthbar_x = 100;
	float p1_healthbar_y = 100;
	std::string p1_healthbar_texture = "content/bop-healthbar-tileset.png";
	Healthbar p1_healthbar(p1_healthbar_texture);

	// Universal player variables
	int player_speed = 400;

	// Create player one
	float p1_x = 100;
	float p1_y = 300;
	int p1_tile_row = 0;
	bool p1_dead = false;
	bool p1_weak_attack = false;
	bool p1_strong_attack = false;
	bool p1_hit_status = false;
	int p1_health = 5;
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

	Player player_1(bop_tileset, player1_height, player1_width, p1_x, p1_y, 1);

	// Create player two
	float p2_x = 800;
	float p2_y = 300;
	int p2_tile_row = 0;
	bool p2_dead = false;
	bool p2_weak_attack = false;
	bool p2_strong_attack = false;
	bool p2_hit_status = false;
	int p2_health = 5;
	int p2_weak_reload_timer = 0;
	int p2_strong_reload_timer = 0;
	float player2_width = 96;
	float player2_height = 96;
	float hitbox2_x = 0;
	float hitbox2_y = 0;
	float hitbox2_width = 100;
	std::string pob_tileset = "content/pob-tilesheet.png";

	Player player_2(pob_tileset, player2_height, player2_width, p2_x, p2_y, 2);

	// Player 2 movement keys
	sf::Keyboard::Key p2_jump_key = sf::Keyboard::Key::P;
	sf::Keyboard::Key p2_crouch_key = sf::Keyboard::Key::SemiColon;
	sf::Keyboard::Key p2_move_left_key = sf::Keyboard::Key::L;
	sf::Keyboard::Key p2_move_right_key = sf::Keyboard::Key::Quote;

	// Player 2 attack keys
	sf::Keyboard::Key p2_weak_attack_key = sf::Keyboard::Key::K;
	sf::Keyboard::Key p2_strong_attack_key = sf::Keyboard::Key::O;

	// Create player 1 projectile
	bool p1_proj_dead = false;
	std::string p1_proj_texture_file = "content/bop-poop.png";
	std::vector<Projectile> p1_proj_vector;

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
		}

		window.clear();
		window.draw(background);

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
		menu.backToMenu(game_running);
		if (!game_running)
		{
			menu.drawButtons(window);
			menu.moveUp();
			menu.moveDown();
			menu.closeGame(window);
			menu.playGame(game_running);
			menu.animateTitle(0, dt);
			menu.drawTitle(window);
		}
		else
		{
			bool p1_tile_collision = false;
			bool p2_tile_collision = false;

			// Draw player 1 healthbar
			p1_healthbar.createHealthbar(p1_healthbar_x, p1_healthbar_y);
			p1_healthbar.drawTo(window);
			p1_healthbar.changeHealthbarTexture(0, p1_health);

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
			player_1.killPlayer(p1_dead, p1_health);
			player_1.movePlayer(player_speed, p1_tile_collision, dt, p1_tile_row, p1_health, p1_move_left_key, p1_move_right_key, p1_jump_key, p1_crouch_key);
			player_1.weakAttackCollision(player_2, p1_weak_attack, p2_hit_status, p2_health);
			player_1.strongAttackCollision(player_2, p1_weak_attack, p1_proj_vector, p1_proj_dead, p2_health);
			player_1.knockbackAnimation(p1_hit_status, p1_tile_row, player_2.returnScale(), p2_dead);
			player_1.collision(screen_width, player1_width, player1_height, hitbox1_x, hitbox1_y, hitbox1_width);
			player_1.attack(p1_tile_row, p1_weak_reload_timer, p1_strong_reload_timer, p1_weak_attack, p1_strong_attack, p1_weak_attack_key, p1_strong_attack_key, p2_dead);
			player_1.crouchAnimation(p1_tile_row, p1_tile_collision, hitbox1_y, player1_height, p1_crouch_key);
			player_1.knockoutAnimation(p1_tile_row, p1_dead, p1_tile_collision);
			player_1.animatePlayer(p1_tile_row, dt);
			player_1.playerPlayerCollision(player_2, p1_move_left_key, p1_move_right_key, player2_width);

			// Draw player 2
			player_2.drawTo(window);
			player_2.killPlayer(p2_dead, p2_health);
			player_2.movePlayer(player_speed, p2_tile_collision, dt, p2_tile_row, p2_health, p2_move_left_key, p2_move_right_key, p2_jump_key, p2_crouch_key);
			player_2.weakAttackCollision(player_1, p2_weak_attack, p1_hit_status, p1_health);
			player_2.strongAttackCollision(player_1, p1_hit_status, p2_proj_vector, p2_proj_dead, p1_health);
			player_2.knockbackAnimation(p2_hit_status, p2_tile_row, player_1.returnScale(), p1_dead);
			player_2.collision(screen_width, player2_width, player2_height, hitbox2_x, hitbox2_y, hitbox2_width);
			player_2.attack(p2_tile_row, p2_weak_reload_timer, p2_strong_reload_timer, p2_weak_attack, p2_strong_attack, p2_weak_attack_key, p2_strong_attack_key, p1_dead);
			player_2.crouchAnimation(p2_tile_row, p2_tile_collision, hitbox2_y, player2_height, p2_crouch_key);
			player_2.knockoutAnimation(p2_tile_row, p2_dead, p2_tile_collision);
			player_2.animatePlayer(p2_tile_row, dt);
			player_2.playerPlayerCollision(player_1, p2_move_left_key, p2_move_right_key, player1_width);

			// Make sure that the projectile gets drawn behind the player.
			// Just change the order of the function calls. Specifically
			// draw projectile call

			// Draw foreground
			left_foreground.drawTo(window);
			right_foreground.drawTo(window);
		}

		window.display();
	}
}