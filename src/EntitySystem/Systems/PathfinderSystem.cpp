#include "PathfinderSystem.hpp"

#include "../Components/Pathfinder.hpp"
#include "../Components/Physical.hpp"
#include "../Components/Movable.hpp"

#include "../../World/World.hpp"
#include "../../Pathfinding/Path.hpp"

#include "../../Math/Math.hpp"

namespace swift
{
	World* PathfinderSystem::world = nullptr;
	
	PathfinderSystem::PathfinderSystem(unsigned int res)
	:	System<Pathfinder>(res)
	{}
		
	void PathfinderSystem::update(float)
	{
		for(auto& c : components)
		{
			Movable& mov = c.getMovable();
			const Physical& phys = mov.getPhysical();
			
			if(world)
			{
				sf::Vector2u tileSize = world->tilemap.getTileSize();
				
				if(c.needsPath)
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
					
					sf::Vector2u nodeStart = {static_cast<unsigned int>(phys.position.x / tileSize.x), static_cast<unsigned int>(phys.position.y / tileSize.y)};
					sf::Vector2u nodeEnd = {static_cast<unsigned int>(c.destination.x / tileSize.x), static_cast<unsigned int>(c.destination.y / tileSize.y)};
					Path path(nodeStart, nodeEnd, nodes);

					c.nodes = path.getNodes();

					if(!c.nodes.empty())
						c.needsPath = false;
				}

				if(!c.nodes.empty())
				{
					sf::Vector2f worldPos = {static_cast<float>(c.nodes.front().getPosition().x) * tileSize.x, static_cast<float>(c.nodes.front().getPosition().y) * tileSize.y};
					if(math::distanceSquared(worldPos, phys.position) <= world->tilemap.getTileSize().x * world->tilemap.getTileSize().x / 16.f)
					{
						c.nodes.pop_front();
						
						if(c.nodes.empty())	// destination reached!
							mov.velocity = {0, 0};
						else					// change direction to next node
							mov.velocity = math::unit(worldPos - phys.position) * mov.moveVelocity;
					}
				}
			}
		}
	}
}
