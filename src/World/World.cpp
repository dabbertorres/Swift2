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
			delete s.second;
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
			s.second->remove(id);
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
