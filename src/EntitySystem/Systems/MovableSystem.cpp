#include "MovableSystem.hpp"

#include "../Components/Movable.hpp"
#include "../Components/Physical.hpp"

namespace swift
{
	void MovableSystem::update(Entity& entity, float dt)
	{
		if(entity.has<Movable>() && entity.has<Physical>())
		{
			entity.get<Physical>()->position.x += entity.get<Movable>()->velocity.x * dt;
			entity.get<Physical>()->position.y += entity.get<Movable>()->velocity.y * dt;
		}
	}
}
