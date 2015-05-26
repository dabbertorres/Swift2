#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include "../Component.hpp"

#include <SFML/System/Vector2.hpp>

namespace swift
{
	class Physical;
	
	class Movable : public Component
	{
		public:
			Movable(unsigned int id, Physical& p);
			
			Movable(const Movable& other);
			
			Movable& operator=(const Movable& other);
			Movable& operator=(Movable&& other);
			
			Physical& getPhysical() const;
			
			static Component::Type type();
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);
			
			float moveVelocity;
			sf::Vector2f velocity;
			
		private:
			Physical& physical;
	};
}

#endif // MOVABLE_HPP
