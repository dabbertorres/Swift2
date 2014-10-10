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
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);
			
			float moveVelocity;
			sf::Vector2f velocity;
	};
}

#endif // MOVABLE_HPP
