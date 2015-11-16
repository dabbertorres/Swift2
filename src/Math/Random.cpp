#include "Random.hpp"

namespace math
{
	namespace swift
	{
		Random Random::rand;
		std::mt19937 Random::generator(std::chrono::system_clock::now().time_since_epoch().count());
		
		Random& get()
		{
			return Random::rand;
		}
		
		Random& rand = get();
	}
}
