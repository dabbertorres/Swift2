#include "MovableSystem.hpp"

#include "../Components/Physical.hpp"

namespace swift
{
	MovableSystem::MovableSystem(unsigned int res)
	:	System<Movable>(res)
	{}
	
	void MovableSystem::update(float dt)
	{
		for(auto& c : components)
		{
			Physical& phys = c.getPhysical();
			
			phys.position.x += c.velocity.x * dt;
			phys.position.y += c.velocity.y * dt;
		}
	}
}
