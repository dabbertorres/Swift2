#include "World.hpp"

namespace swift
{
	World::World(const sf::Vector2i& s, AssetManager& am)
		:	assets(am),
			size(s)
	{
	}
	
	World::~World()
	{
		for(auto& e : entities)
		{
			delete e;
		}
	}
	
	Entity* World::addEntity()
	{
		unsigned oldSize = entities.size();
		
		entities.emplace_back(new Entity);
		
		return entities.size() > oldSize ? entities[entities.size() - 1] : nullptr;
	}
	
	bool World::removeEntity(int e)
	{
		// if e is positive, check if is greater than last entity
		// if e is negative, check if it refers to entity less than 0
		if(e >= static_cast<int>(entities.size()) || static_cast<int>(entities.size()) + e < 0)
			return false;
		
		entities.erase((e >= 0 ? entities.begin() : entities.end()) + e);
		
		return true;
	}
	
	const std::vector<Entity*>& World::getEntities()
	{
		return entities;
	}
}
