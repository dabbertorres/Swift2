#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include "../Component.hpp"

#include <SFML/System/Vector2.hpp>

namespace swift
{
	class Movable : public Component
	{
		public:
			Movable();
			
			static std::string getType();
			
			float moveVelocity;
			sf::Vector2f velocity;
	};
}

#endif // MOVABLE_HPP
