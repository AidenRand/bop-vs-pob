#include "game.hpp"
#include "menu.hpp"
#include "clouds.hpp"
#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "players.hpp"

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

	// Set background
	sf::Sprite background;
	sf::Texture background_texture;
	if (!background_texture.loadFromFile("content/bop-vs-pob-bckgr.png"))
	{
		std::cout << "ERROR::Could not load background from file" << "\n";
	}
	background.setTexture(background_texture);

	// Create menu
	Menu menu;
	int menu_font_size = 30;
	float title_x = 230;
	float title_y = -130;
	menu.createButtons(screen_width, screen_height, menu_font_size);
	menu.createTitle(title_x, title_y);

	// Create players
	Players player_1(50, 50, 100, 100);

	// Create map
	const int map_height = 4;
	const int map_width = 26;

	sf::String tile_map[map_height] =
	{
			"               MM                ",
			"                                 ",
			"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
			"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"
	};

	World world_map;

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

		player_1.movePlayers();
		player_1.drawTo(window);

		world_map.createMap(tile_map, map_width, map_height);

		window.display();
	}
}