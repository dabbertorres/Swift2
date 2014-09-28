#include "PhysicalSystem.hpp"

#include "../Components/Physical.hpp"

#include <cmath>

namespace swift
{
	void PhysicalSystem::update(Entity& entity, float /*dt*/)
	{
		if(entity.has<Physical>())
		{
			// collision handling code
		}
	}
	
	float PhysicalSystem::distance(sf::Vector2f one, sf::Vector2f two) const
	{
		return std::sqrt(std::pow(two.x - one.x, 2) + std::pow(two.y - one.y, 2));
	}
}
