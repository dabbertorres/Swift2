#include "PathfinderSystem.hpp"

#include "../Components/Pathfinder.hpp"
#include "../../World/World.hpp"
#include "../../Pathfinding/Path.hpp"

#include "../../Math/Math.hpp"

namespace swift
{
	World* PathfinderSystem::world = nullptr;

	void PathfinderSystem::update(const std::vector<Entity>& entities, float)
	{
		for(auto& e : entities)
		{
			if(e.has<Pathfinder>() && e.has<Physical>() && e.has<Movable>())
			{
				Pathfinder* pf = e.get<Pathfinder>();
				Physical* phys = e.get<Physical>();
				Movable* mov = e.get<Movable>();
				
				if(world)
				{
					if(pf->needsPath)
					{

						Path path(phys->position, pf->destination, phys->zIndex, world->tilemap);

						pf->nodes = path.getNodes();

						if(!pf->nodes.empty())
							pf->needsPath = false;
					}

					if(!pf->nodes.empty())
					{
						if(math::distanceSquared(pf->nodes.front().getPosition(), phys->position) <= world->tilemap.getTileSize().x * world->tilemap.getTileSize().x / 16.f)
						{
							pf->nodes.pop_front();
							
							if(pf->nodes.empty())	// destination reached!
								mov->velocity = {0, 0};
							else					// change direction to next node
								mov->velocity = math::unit(pf->nodes.front().getPosition() - phys->position) * mov->moveVelocity;
						}
					}
				}
			}
		}
	}
}
