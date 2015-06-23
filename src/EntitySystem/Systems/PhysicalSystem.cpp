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
				if(c1.second.ID() != c2.second.ID())
				{
					Collision col(c1.second, c2.second);
					
					if(collisions.back().getResult())
					{
						collisions.push_back(col);
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
