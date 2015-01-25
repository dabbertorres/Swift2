#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/System/Vector2.hpp>

namespace swift
{
	class Entity;
	
	class Collision
	{
		public:
			Collision(const Entity& f, const Entity& s);
			
			const Entity& getFirstEntity() const;
			const Entity& getSecondEntity() const;
			
			const sf::Vector2f& getPosition() const;
			
			bool getResult() const;
			
		private:
			bool handle();
			
			bool circularCollision();
			bool separatingAxisTheorem();
			
			static sf::Vector2f scaledDiffVector(const sf::Vector2f& oneVec, const sf::Vector2f& twoVec, float scale);
			
			const Entity& one;
			const Entity& two;
			sf::Vector2f position;
			
			bool result;
	};
}

#endif // COLLISION_HPP
