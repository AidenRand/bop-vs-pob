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

void Players::movePlayers(int player_speed, bool& player_tile_collision)
{
	sf::Vector2f velocity;

	std::cout << player_speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y -= step_y;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.y += step_y;
		tileCollision(player_tile_collision);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = step_x;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = -step_x;
	}

	player.move(velocity);
}

void Players::tileCollision(bool& player_tile_collision)
{
	player_top = player.getPosition().y;
	player_bottom = player.getPosition().y + 50;
	player_left = player.getPosition().x;
	player_right = player.getPosition().x + player.getTextureRect().width;

	if (player_tile_collision)
	{
		step_y *= -1;
	}
}