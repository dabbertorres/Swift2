#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

#include <SFML/System/Vector2.hpp>

namespace swift
{
	namespace math
	{
		constexpr float PI = 3.14159265359;
		
		/* vector math */
		template<typename T>
		T magnitude(const sf::Vector2<T>& vec)
		{
			return std::sqrt(vec.x * vec.x + vec.y * vec.y);
		}

		template<typename T>
		sf::Vector2<T> unit(const sf::Vector2<T>& vec)
		{
			T mag = magnitude(vec);

			if(mag == 0)
			{
				return {0, 0};
			}
			
			return vec / mag;
		}

		template<typename T>
		T dot(const sf::Vector2<T>& one, const sf::Vector2<T>& two)
		{
			return one.x * two.x + one.y * two.y;
		}

		// projection of one onto two
		template<typename T>
		T projection(const sf::Vector2<T>& one, const sf::Vector2<T>& two)
		{
			return dot(one, unit(two));
		}

		template<typename T>
		sf::Vector2<T> normalY(const sf::Vector2<T>& vec)
		{
			sf::Vector2<T> nonNormalized(-vec.y, vec.x);
			return unit(nonNormalized);
		}

		template<typename T>
		sf::Vector2<T> normalX(const sf::Vector2<T>& vec)
		{
			sf::Vector2<T> nonNormalized(vec.y, -vec.x);
			return unit(nonNormalized);
		}

		/* distance math */
		template<typename T>
		T distance(const sf::Vector2<T>& one, const sf::Vector2<T>& two)
		{
			return std::sqrt((two.x - one.x) * (two.x - one.x) + (two.y - one.y) * (two.y - one.y));
		}

		template<typename T>
		T distanceSquared(const sf::Vector2<T>& one, const sf::Vector2<T>& two)
		{
			return (two.x - one.x) * (two.x - one.x) + (two.y - one.y) * (two.y - one.y);
		}
		
		template<typename T>
		T lerp(T p0, T p1, double w)
		{
			return (1.f - w) * p0 + w * p1;
		}
	}
}

#endif // MATH_HPP
