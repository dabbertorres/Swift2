#include "Random.hpp"

namespace swift
{
	namespace math
	{
		Random* Random::rand = nullptr;
		std::mt19937 Random::generator(std::chrono::system_clock::now().time_since_epoch().count());
		
		Random& Random::get()
		{
			if(!rand)
			{
				rand = new Random();
			}
			
			return *rand;
		}
		
		Random& rand = Random::get();
	}
}
