#include "players.hpp"

Players::Players(float player_width, float player_height, float player_x, float player_y)
{
	player.setFillColor(sf::Color::White);
	player.setSize(sf::Vector2f(player_width, player_height));
	player.setPosition(sf::Vector2f(player_x, player_y));
}

void Players::drawTo(sf::RenderWindow& window)
{
	window.draw(player);
}

void Players::movePlayers(int player_speed, bool& player_tile_collision, float& dt)
{
	velocity.x = 0;

	// velocity.y += gravity;
	if (player_tile_collision)
	{
		velocity.y = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			velocity.y -= 800;
		}
	}
	else
	{
		velocity.y += gravity;
	}

	std::cout << gravity << "\n";

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = player_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = -player_speed;
	}

	player.move(velocity * dt);
}

void Players::collision(float screen_width, int player_width)
{

	player_top = player.getPosition().y;
	player_bottom = player.getPosition().y + player_width;
	player_left = player.getPosition().x;
	player_right = player.getPosition().x + player.getTextureRect().width;

	//  If player goes beyond screen borders, set player position
	// to just before screen border
	if (player_right > screen_width - player_width)
	{
		player.setPosition(screen_width - player_width, player.getPosition().y);
	}
	else if (player_left < 0)
	{
		player.setPosition(0, player.getPosition().y);
	}
}