#include "World.hpp"

#include <cmath>
#include "../Math/Math.hpp"

namespace swift
{
	World::World(const std::string& n)
	:	name(n)
	{
		entities.reserve(128);
	}
	
	World::~World()
	{
		for(auto& s : systems)
		{
			delete s;
		}
	}
	
	unsigned int World::createEntity(unsigned int id)
	{
		if(id == 0)
			//id =	// generate a random id
		
		entities.emplace_back(id);
		
		return id;
	}
	
	bool World::destroyEntity(int e)
	{
		// if e is positive, check if is greater than last entity
		// if e is negative, check if it refers to entity less than 0
		if(e > static_cast<int>(entities.size()) || static_cast<int>(entities.size()) + e < 0)
			return false;
		
		unsigned int id = entities[e];
		entities.erase((e >= 0 ? entities.begin() : entities.end()) + e);
		
		for(auto& s : systems)
		{
			s->remove(id);
		}
		
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
}
