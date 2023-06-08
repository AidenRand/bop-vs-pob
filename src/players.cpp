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

void Players::movePlayers()
{
	sf::Vector2f velocity;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.y = 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.y = -5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x = -5;
	}

	player.move(velocity);
}