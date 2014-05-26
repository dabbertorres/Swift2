#include "Player.hpp"

namespace swift
{
	Player::Player(const sf::Texture& tex/*, const Bitmask& btm*/)
		:	Drawable(tex),
			Collidable(getSprite()/*, btm*/)
	{
		addID(Physical::getID());
		addID(Drawable::getID());
		addID(Collidable::getID());
	}

	Player::~Player()
	{
	}
}
