#include "World.hpp"

#include "Math/Math.hpp"
#include "Math/Random.hpp"

namespace swift
{
	World::World(const std::string& n, unsigned int res)
	:	name(n)
	{
		entities.reserve(res);
	}
	
	World::~World()
	{
		for(auto& s : systems)
		{
			delete s;
		}
	}
	
	bool World::createEntity(unsigned int id)
	{
		if(entities.size() == entities.capacity())
		{
			return false;
		}
		
		if(std::find(entities.begin(), entities.end(), id) != entities.end())
		{
			return false;
		}
		
		entities.emplace_back(id);
		
		return true;
	}
	
	bool World::destroyEntity(unsigned int id)
	{
		auto erase = std::find(entities.begin(), entities.end(), id);
		
		if(erase == entities.end())
		{
			return false;
		}
		
		for(auto& s : systems)
		{
			s->remove(id);
		}
		
		entities.erase(erase);
		
		return true;
	}
	
	unsigned int World::getPlayer() const
	{
		return player;
	}
	
	const std::vector<unsigned int>& World::getEntities() const
	{
		return entities;
	}
	
	std::vector<unsigned int> World::getEntitiesAround(const sf::Vector2f& pos, float radius) const
	{
		std::vector<unsigned int> around;
		
		// if pos is outside of the world, or the radius is 0 or less, just return an empty vector
		if(!(0 <= pos.x && 0 <= pos.y) || radius <= 0)
			return around;
		
		/*for(auto& id : entities)
		{
			if(physicalSystem.has(id))
			{
				Physical& p = physicalSystem.get(id);
				if(math::distance(p.position, pos) <= radius)
					around.push_back(id);
			}
		}*/
		
		return around;
	}
	
	const std::string& World::getName() const
	{
		return name;
	}
	
	const SystemMap& World::getSystems() const
	{
		return systems;
	}
	
	SystemMap& World::getSystems()
	{
		return systems;
	}
}
