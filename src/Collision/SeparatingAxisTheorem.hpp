#ifndef SEPARATING_AXIS_THEOREM_HPP
#define SEPARATING_AXIS_THEOREM_HPP

namespace swift
{
	float dotProduct(sf::Vector2f one, sf::Vector2f two)
	{
		return one.x * two.x + one.y * two.y;
	}
	
	float dotProduct(float a, float b, float theta)
	{
		return a * b * std::cos(theta);
	}
}

#endif // SEPARATING_AXIS_THEOREM_HPP