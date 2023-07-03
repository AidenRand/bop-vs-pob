#ifndef HITBOX_HPP
#define HITBOX_HPP

#include <SFML/Graphics.hpp>

class HitboxSprite : public sf::Sprite
{
public:
	void setHitbox(const sf::FloatRect& hitbox)
	{
		m_hitbox = hitbox;
	}

	sf::FloatRect getGlobalHitbox() const {
		return getTransform().transformRect(m_hitbox);
	}

private:
	sf::FloatRect m_hitbox;
};

#endif