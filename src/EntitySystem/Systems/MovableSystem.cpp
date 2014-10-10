#include "MovableSystem.hpp"

#include "../Components/Movable.hpp"
#include "../Components/Physical.hpp"

namespace swift
{
	void MovableSystem::update(Entity& entity, float dt)
	{
		if(entity.has<Movable>() && entity.has<Physical>())
		{
			Physical* phys = entity.get<Physical>();
			Movable* mov = entity.get<Movable>();
			phys->position.x += mov->velocity.x * dt;
			phys->position.y += mov->velocity.y * dt;
		}
	}
}
