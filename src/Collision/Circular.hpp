#ifndef CIRCULAR_HPP
#define CIRCULAR_HPP

#include <SFML/System/Vector2.hpp>

namespace swift
{
	struct Circle
	{
		Circle(sf::Vector2f pos, float rad, sf::Vector2f vel)
			: position(pos), radius(rad), velocity(vel)
		{}
			
		sf::Vector2f position;
		float radius;
		sf::Vector2f velocity;
	};
	
	inline bool circularCollision(Circle c1, Circle c2)
	{
		bool pen = (c2.position.x - c1.position.x) * (c2.position.x - c1.position.x) + (c2.position.y - c1.position.y) * (c2.position.y - c1.position.y) < (c1.radius + c2.radius);
		if(!pen)
			return false;
		return true;
	}
}

#endif // CIRCULAR_HPP