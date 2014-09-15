#include "World.hpp"

namespace swift
{
	World::World(const sf::Vector2u& s)
		:	size(s)
	{
	}

	World::~World()
	{
	}
	
	const std::vector<Entity>& World::getEntities() const
	{
		return entities;
	}
}
