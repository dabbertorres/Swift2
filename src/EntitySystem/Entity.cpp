#include "Entity.hpp"

#include <algorithm>

namespace swift
{
	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
	}
	
	bool Entity::has(unsigned id)
	{
		return std::find(components.begin(), components.end(), id) != components.end();
	}
	
	void Entity::addID(unsigned id)
	{
		components.push_back(id);
	}
}
