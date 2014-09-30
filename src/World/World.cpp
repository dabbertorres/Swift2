#include "World.hpp"

#include <cmath>

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
	
	const std::vector<Entity*>& World::getEntities() const
	{
		return entities;
	}
	
	const std::vector<Entity*>& World::calculateEntitiesAround(sf::Vector2f pos, float radius)
	{
		entitiesAround.clear();
		// if pos is outside of the world, or the radius is 0 or less, just return an empty vector
		if(!(0 <= pos.x && pos.x < size.x && 0 <= pos.y && pos.y < size.y) || radius <= 0)
			return entitiesAround;
		
		for(auto& e : entities)
		{
			if(e->has<Physical>())
			{
				Physical* p = e->get<Physical>();
				if(distance(p->position, pos) <= radius)
					entitiesAround.push_back(e);
			}
		}
		
		return entitiesAround;
	}
	
	const std::vector<Entity*>& World::getEntitiesAround() const
	{
		return entitiesAround;
	}
	
	float World::distance(sf::Vector2f one, sf::Vector2f two) const
	{
		return std::sqrt(std::pow(two.x - one.x, 2) + std::pow(two.y - one.y, 2));
	}
}
