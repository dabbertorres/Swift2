#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

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
			return vec / magnitude(vec);
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
		sf::Vector2<T> normal(const sf::Vector2<T>& vec)
		{
			sf::Vector2<T> nonNormalized(-vec.y, vec.x);
			return unit(nonNormalized);
		}

		/* distance math */
		inline float distance(const sf::Vector2f& one, const sf::Vector2f& two)
		{
			return std::sqrt((two.x - one.x) * (two.x - one.x) + (two.y - one.y) * (two.y - one.y));
		}

		inline float distanceSquared(const sf::Vector2f& one, const sf::Vector2f& two)
		{
			return (two.x - one.x) * (two.x - one.x) + (two.y - one.y) * (two.y - one.y);
		}
	}
}

#endif // MATH_HPP
