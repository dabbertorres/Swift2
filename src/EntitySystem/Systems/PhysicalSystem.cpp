#include "PhysicalSystem.hpp"

#include "../Components/Physical.hpp"

namespace swift
{
	void PhysicalSystem::update(Entity& entity, float /*dt*/)
	{
		if(entity.has<Physical>())
		{
			// collision handling code
		}
	}
}
