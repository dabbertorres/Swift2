#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Entity.hpp"
#include "../Components/Physical.hpp"
#include "../Components/Drawable.hpp"
#include "../Components/Collidable.hpp"

namespace swift
{
	class Player : public Entity, public Physical, public Drawable, public Collidable
	{
		public:
			Player(const sf::Texture& tex/*, const Bitmask& btm*/);
			~Player();

	};
}

#endif // PLAYER_HPP
