#include "PhysicalSystem.hpp"

#include "../Components/Physical.hpp"

namespace swift
{
	void PhysicalSystem::update(const std::vector<Entity>& entities, float /*dt*/)
	{
		collisions.clear();
		
		for(auto& e1 : entities)
		{
			for(auto& e2 : entities)
			{
				if(&e1 != &e2)
				{
					if(e1.has<Physical>() && e2.has<Physical>())
					{
						collisions.emplace_back(e1, e2);
						
						if(!collisions.back().getResult())
						{
							collisions.pop_back();
						}
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
