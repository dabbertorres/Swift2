#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/System/Vector2.hpp>

namespace swift
{
	class Entity;
	
	class Collision
	{
		public:
			Collision(Entity& f, Entity& s);
			
			Entity& getFirstEntity() const;
			Entity& getSecondEntity() const;
			
			const sf::Vector2f& getPosition() const;
			
			bool getResult() const;
			
		private:
			bool handle();
			
			static sf::Vector2f scaledDiffVector(const sf::Vector2f& one, const sf::Vector2f& two, float scale);
			
			Entity& one;
			Entity& two;
			sf::Vector2f position;
			
			bool result;
	};
}

#endif // COLLISION_HPP
