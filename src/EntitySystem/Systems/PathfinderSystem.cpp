#include "PathfinderSystem.hpp"

#include "../Components/Pathfinder.hpp"

#include "../../Math/Math.hpp"

namespace swift
{
	void PathfinderSystem::update(std::vector<Entity*>& entities, float)
	{
		for(auto& e : entities)
		{
			if(e->has<Pathfinder>() && e->has<Physical>() && e->has<Movable>())
			{
				Pathfinder* pf = e->get<Pathfinder>();
				Physical* phys = e->get<Physical>();
				Movable* mov = e->get<Movable>();
				
				if(!pf->nodes.empty())
				{
					if(math::distanceSquared(pf->nodes.front(), phys->position) < 4.f)
					{
						pf->nodes.pop_front();
						
						if(pf->nodes.empty())	// destination reached!
							mov->velocity = {0, 0};
						else
							mov->velocity = math::unit(pf->nodes.front() - phys->position) * mov->moveVelocity;
					}
				}
			}
		}
	}
}
