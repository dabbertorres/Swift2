#ifndef SWIFT_RANDOM_HPP
#define SWIFT_RANDOM_HPP

#include <random>
#include <chrono>

namespace swift
{
	namespace math
	{
		class Random
		{
			public:
				template<typename T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
				T operator()(T low, T high)
				{
					return std::uniform_int_distribution<T>(low, high)(generator);
				}
				
				template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
				T operator()(T low, T high)
				{
					return std::uniform_real_distribution<T>(low, high)(generator);
				}
				
				static Random& get();
				
			private:
				Random() {};
				
				static Random* rand;
				static std::mt19937 generator;
		};
		
		extern Random& rand;
	}
}

#endif // SWIFT_RANDOM_HPP
