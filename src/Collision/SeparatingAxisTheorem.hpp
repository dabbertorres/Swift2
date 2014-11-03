#ifndef SEPARATING_AXIS_THEOREM_HPP
#define SEPARATING_AXIS_THEOREM_HPP

#include <cmath>
#include <SFML/System/Vector2.hpp>

namespace swift
{
	inline float dotProduct(const sf::Vector2f& one, const sf::Vector2f& two)
	{
		return one.x * two.x + one.y * two.y;
	}
	
	inline float dotProduct(float a, float b, float theta)
	{
		return a * b * std::cos(theta);
	}
}

#endif // SEPARATING_AXIS_THEOREM_HPP