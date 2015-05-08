#include "PhysicalSystem.hpp"

#include "../Components/Physical.hpp"

namespace swift
{
	void PhysicalSystem::update(float /*dt*/)
	{
		collisions.clear();
		
		for(auto& c1 : components)
		{
			for(auto& c2 : components)
			{
				if(c1.ID() != c2.ID())
				{
					collisions.emplace_back(c1, c2);
						
					if(!collisions.back().getResult())
					{
						collisions.pop_back();
					}
				}
			}
		}
	}
	
	const std::vector<Collision>& PhysicalSystem::getCollisions() const
	{
		return collisions;
	}
}
