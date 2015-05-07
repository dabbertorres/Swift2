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
					sf::Vector2u tileSize = world->tilemap.getTileSize();
					
					if(pf->needsPath)
					{
						Path::NodesMap nodes;
						
						// build path map
						for(int i = 0; world->tilemap.getTile(i, 0) != nullptr; i++)
						{
							for(int j = 0; world->tilemap.getTile(i, j) != nullptr; j++)
							{
								nodes[i][j] = world->tilemap.getTile(i, j)->isPassable();
							}
						}
						
						sf::Vector2u nodeStart = {static_cast<unsigned int>(phys->position.x / tileSize.x), static_cast<unsigned int>(phys->position.y / tileSize.y)};
						sf::Vector2u nodeEnd = {static_cast<unsigned int>(pf->destination.x / tileSize.x), static_cast<unsigned int>(pf->destination.y / tileSize.y)};
						Path path(nodeStart, nodeEnd, nodes);

						pf->nodes = path.getNodes();

						if(!pf->nodes.empty())
							pf->needsPath = false;
					}

					if(!pf->nodes.empty())
					{
						sf::Vector2f worldPos = {static_cast<float>(pf->nodes.front().getPosition().x) * tileSize.x, static_cast<float>(pf->nodes.front().getPosition().y) * tileSize.y};
						if(math::distanceSquared(worldPos, phys->position) <= world->tilemap.getTileSize().x * world->tilemap.getTileSize().x / 16.f)
						{
							pf->nodes.pop_front();
							
							if(pf->nodes.empty())	// destination reached!
								mov->velocity = {0, 0};
							else					// change direction to next node
								mov->velocity = math::unit(worldPos - phys->position) * mov->moveVelocity;
						}
					}
				}
			}
		}
	}
}
