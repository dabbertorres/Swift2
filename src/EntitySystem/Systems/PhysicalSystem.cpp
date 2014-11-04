#include "PhysicalSystem.hpp"

#include "../Components/Physical.hpp"

#include "../../Collision/Collision.hpp"

namespace swift
{
	void PhysicalSystem::update(const std::vector<Entity*>& entities, float /*dt*/)
	{
		for(auto& c : collisions)
			delete c;
		
		collisions.clear();
		
		for(auto& e1 : entities)
		{
			for(auto& e2 : entities)
			{
				if(e1 != e2)
				{
					if(e1->has<Physical>() && e2->has<Physical>())
					{
						if(e1->get<Physical>()->collides && e2->get<Physical>()->collides)
						{
							collisions.emplace_back(new Collision(*e1, *e2));
							
							if(!collisions.back()->getResult())
							{
								delete collisions.back();
								collisions.pop_back();
							}
						}
					}
				}
			}
		}
	}
	
	std::vector<Collision*> PhysicalSystem::getCollisions() const
	{
		return collisions;
	}
}
