#ifndef PROJECTION_HPP
#define PROJECTION_HPP

/* this class describes the projection of a 4 vertex shape
 * onto a given axis
 */
 
#include "../Math/Math.hpp"

namespace swift
{
	template<typename T>
	class Projection
	{
		public:
			Projection(sf::Vector2<T> axis, sf::Vector2<T> vertices[4])
			{
				min = math::dot(axis, vertices[0]);
				max = min;
				
				for(int i = 1; i < 4; i++)
				{
					T p = math::dot(axis, vertices[i]);
					
					if(p < min)
						min = p;
					else if(p > max)
						max = p;
				}
			}
			
			T getMin() const
			{
				return min;
			}
			
			T getMax() const
			{
				return max;
			}
			
			T overlap(const Projection<T>& other)
			{
				if(other.getMin() <= max && max <= other.getMax())
					return max - other.getMin();
				else if(min <= other.getMax() && other.getMax() <= max)
					return other.getMax() - min;
				else
					return 0;
			}
			
		private:
			T min;
			T max;
	};
}

#endif // PROJECTION_HPP
