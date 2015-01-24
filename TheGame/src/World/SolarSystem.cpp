#include "SolarSystem.hpp"

namespace tg
{
	SolarSystem::SolarSystem(unsigned int size)
	{
		bodies.reserve(size);
	}

	SolarSystem::~SolarSystem()
	{
	}
}
