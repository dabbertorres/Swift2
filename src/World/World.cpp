#include "World.hpp"

namespace swift
{
	World::World(const sf::Vector2i& s, AssetManager& am)
		:	assets(am),
			size(s)
	{
	}
	
	std::vector<Entity>& World::getEntities()
	{
		return entities;
	}
	
	Entity& World::addEntity()
	{
		entities.emplace_back();
		return entities.back();
	}
}
