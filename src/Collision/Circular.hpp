#ifndef CIRCULAR_HPP
#define CIRCULAR_HPP

namespace swift
{
	struct Circle
	{
		Circle(sf::Vector2f pos, float rad)
		{
			position = pos;
			radius = rad;
		}
		
		sf::Vector2f position;
		float radius;
	}
	
	float circleCollision(Circle c1, Circle c2)
	{
		
	}
}

#endif // CIRCULAR_HPP