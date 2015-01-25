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
	
	Entity* World::addEntity()
	{
		unsigned oldSize = entities.size();
		
		entities.emplace_back(entities.size() - 1);
		
		return entities.size() > oldSize ? &entities[entities.size() - 1] : nullptr;
	}
	
	bool World::removeEntity(int e)
	{
		// if e is positive, check if is greater than last entity
		// if e is negative, check if it refers to entity less than 0
		if(e > static_cast<int>(entities.size()) || static_cast<int>(entities.size()) + e < 0)
			return false;
		
		entities.erase((e >= 0 ? entities.begin() : entities.end()) + e);
		
		return true;
	}
	
	Entity* World::getEntity(int e)
	{
		// if e is positive, check if is greater than last entity
		// if e is negative, check if it refers to entity less than 0
		if(e > static_cast<int>(entities.size()) || static_cast<int>(entities.size()) + e < 0)
			return nullptr;
			
		return &entities[(e >= 0 ? 0 : entities.size()) + e];
	}
	
	Entity* World::getPlayer()
	{
		for(auto& e : entities)
		{
			if(e.has<Controllable>())
				return &e;
		}
		
		return nullptr;
	}
	
	std::vector<Entity*> World::getEntities()
	{
		std::vector<Entity*> entityPtrs;
		
		for(auto& e : entities)
		{
			entityPtrs.push_back(&e);
		}
		
		return entityPtrs;
	}
	
	std::vector<Entity*> World::getEntitiesAround(const sf::Vector2f& pos, float radius)
	{
		std::vector<Entity*> around;
		
		// if pos is outside of the world, or the radius is 0 or less, just return an empty vector
		if(!(0 <= pos.x && 0 <= pos.y) || radius <= 0)
			return around;
		
		for(auto& e : entities)
		{
			if(e.has<Physical>())
			{
				Physical* p = e.get<Physical>();
				if(math::distance(p->position, pos) <= radius)
					around.push_back(&e);
			}
		}
		
		return around;
	}
	
	std::vector<unsigned> World::getEntitiesAroundIDs(const sf::Vector2f& pos, float radius)
	{
		std::vector<unsigned> around;
		
		if(!(0 <= pos.x && 0 <= pos.y) || radius <= 0)
			return around;
		
		for(unsigned i = 0; i < entities.size(); i++)
		{
			if(entities[i].has<Physical>())
			{
				Physical* p = entities[i].get<Physical>();
				
				if(math::distance(p->position, pos) <= radius)
					around.push_back(i);
			}
		}
		
		return around;
	}
	
	const std::string& World::getName() const
	{
		return name;
	}
}
