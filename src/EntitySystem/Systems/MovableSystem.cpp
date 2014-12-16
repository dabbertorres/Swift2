#include "MovableSystem.hpp"

#include "../Components/Movable.hpp"
#include "../Components/Physical.hpp"

namespace swift
{
	void MovableSystem::update(std::vector<Entity*>& entities, float dt)
	{
		for(auto& e : entities)
		{
			if(e->has<Movable>() && e->has<Physical>())
			{
				Physical* phys = e->get<Physical>();
				Movable* mov = e->get<Movable>();
				
				phys->position.x += mov->velocity.x * dt;
				phys->position.y += mov->velocity.y * dt;
			}
		}
	}
}
