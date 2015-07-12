#include "PathfinderSystem.hpp"

#include "../Components/Pathfinder.hpp"
#include "../Components/Physical.hpp"
#include "../Components/Movable.hpp"

#include "World/World.hpp"
#include "Pathfinding/Path.hpp"

#include "Math/Math.hpp"

namespace swift
{
	World* PathfinderSystem::world = nullptr;
	
	PathfinderSystem::PathfinderSystem()
	:	physSystem(nullptr),
		moveSystem(nullptr)
	{}
	
	void PathfinderSystem::update(float)
	{
		if(!world || !physSystem || !moveSystem)
		{
			return;
		}
		
		for(auto& c : components)
		{
			Movable* mov = moveSystem->get(c.second.ID());
			const Physical* phys = physSystem->get(c.second.ID());
			
			sf::Vector2u tileSize = world->tilemap.getTileSize();
				
			if(c.second.needsPath)
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
				sf::Vector2u nodeEnd = {static_cast<unsigned int>(c.second.destination.x / tileSize.x), static_cast<unsigned int>(c.second.destination.y / tileSize.y)};
				Path path(nodeStart, nodeEnd, nodes);

				c.second.nodes = path.getNodes();

				if(!c.second.nodes.empty())
					c.second.needsPath = false;
			}

			if(!c.second.nodes.empty())
			{
				sf::Vector2f worldPos = {static_cast<float>(c.second.nodes.front().getPosition().x) * tileSize.x, static_cast<float>(c.second.nodes.front().getPosition().y) * tileSize.y};
				if(math::distanceSquared(worldPos, phys->position) <= world->tilemap.getTileSize().x * world->tilemap.getTileSize().x / 16.f)
				{
					c.second.nodes.pop_front();
					
					if(c.second.nodes.empty())	// destination reached!
						mov->velocity = {0, 0};
					else					// change direction to next node
						mov->velocity = math::unit(worldPos - phys->position) * mov->moveVelocity;
				}
			}
		}
	}
}
