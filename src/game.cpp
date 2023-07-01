#include "game.hpp"
#include "menu.hpp"
#include "clouds.hpp"
#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "player.hpp"
#include "foreground.hpp"
#include "projectile.hpp"

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
		std::cout << "ERROR::Could not load background from file" << "\n";
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

	// Universal player variables
	int player_speed = 400;
	float player_width = 96;
	float player_height = 96;
	float hitbox_x = 0;
	float hitbox_y = 0;

	// Create player one
	float p1_x = 100;
	float p1_y = 300;
	bool p1_weak_attack = false;
	bool p1_strong_attack = false;
	int p1_health = 5;
	int p1_tile_row = 0;
	int p1_weak_reload_timer = 0;
	int p1_strong_reload_timer = 0;
	std::string bop_tileset = "content/bop-tilesheet.png";
	Player player_1(bop_tileset, player_height, player_width, p1_x, p1_y);

	// Create player 2
	float p2_x = 800;
	float p2_y = 300;
	// bool p2_weak_attack = false;
	// bool p2_strong_attack = false;
	int p2_health = 5;
	int p2_tile_row = 0;
	// int p2_weak_reload_timer = 0;
	// int p2_strong_reload_timer = 0;
	std::string pob_tileset = "content/pob-tilesheet.png";
	Player player_2(pob_tileset, player_height, player_width, p2_x, p2_y);

	// Create player 1 projectile
	bool proj_dead = false;
	std::string proj_texture_file = "content/bop-poop.png";
	std::vector<Projectile> p1_proj_vector;

	// Create map
	const int map_height = 17;
	const int map_width = 30;
	int tile_width = 32;
	int tile_height = 32;

	World world_map;
	sf::String tile_map[map_height] =
	{
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
		else {
			bool p1_tile_collision = false;
			bool p2_tile_collision = false;

			// Draw tile map if game is running
			world_map.createMap(tile_map, map_width, map_height, tile_width, tile_height, window, player_1, player_2, p1_tile_collision, p2_tile_collision, player_width);

			// Draw player 1 projectile
			Projectile p1_proj(proj_texture_file);
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
				p1_proj_vector[i].killProj(proj_dead, screen_width);


				if (proj_dead)
				{
					p1_proj_vector.erase(p1_proj_vector.begin() + i);
					proj_dead = false;
				}
			}

			// Draw player 1
			player_1.drawTo(window);
			player_1.movePlayer(player_speed, p1_tile_collision, dt, p1_tile_row, p1_health);
			player_1.collision(screen_width, player_width, player_height, hitbox_x, hitbox_y);
			player_1.attack(p1_tile_row, p1_weak_reload_timer, p1_strong_reload_timer, p1_weak_attack, p1_strong_attack);
			player_1.crouchAnimation(p1_tile_row, p1_tile_collision, hitbox_y, player_height);
			player_1.knockoutAnimation(p1_tile_row, p1_health);
			player_1.animatePlayer(p1_tile_row, dt);

			// Draw player 2
			player_2.drawTo(window);
			player_2.movePlayer2(player_speed, p2_tile_collision, dt, p2_tile_row, p2_health);
			player_2.collision(screen_width, player_width, player_height, hitbox_x, hitbox_y);
			player_2.animatePlayer(p2_tile_row, dt);

			// Draw foreground
			left_foreground.drawTo(window);
			right_foreground.drawTo(window);
		}

		window.display();
	}
}