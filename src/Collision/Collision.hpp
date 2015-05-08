#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <SFML/System/Vector2.hpp>

namespace swift
{
	class Physical;
	class MovableSystem;
	
	class Collision
	{
		public:
			Collision(Physical& o, Physical& t);
			
			unsigned int getFirstID() const;
			unsigned int getSecondID() const;
			
			const sf::Vector2f& getPosition() const;
			
			bool getResult() const;
			
			static const MovableSystem* movables;
			
		private:
			bool handle();
			
			bool circularCollision();
			bool separatingAxisTheorem();
			
			static sf::Vector2f scaledDiffVector(const sf::Vector2f& oneVec, const sf::Vector2f& twoVec, float scale);
			
			Physical& one;
			Physical& two;
			unsigned int idOne;
			unsigned int idTwo;
			sf::Vector2f position;
			
			bool result;
	};
}

#endif // COLLISION_HPP
