#include "EntitySystem.hpp"

namespace swift
{
	EntitySystem::EntitySystem()
	{
	}

	EntitySystem::~EntitySystem()
	{
		for(auto& e : entities)
			if(e)
				delete e;
	}
	
	Entity& EntitySystem::create()
	{
		entities.emplace_back();
		return *entities[entities.size() - 1];
	}
	
	unsigned EntitySystem::getSize() const
	{
		return entities.size();
	}		
	
	std::vector<Entity*>& EntitySystem::getEntities()
	{
		return entities;
	}
}
