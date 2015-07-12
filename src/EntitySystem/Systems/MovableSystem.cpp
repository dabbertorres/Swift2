#include "MovableSystem.hpp"

#include "../Components/Physical.hpp"

namespace swift
{
	MovableSystem::MovableSystem()
	:	physSystem(nullptr)
	{}
	
	void MovableSystem::update(float dt)
	{
		if(!physSystem)
		{
			return;
		}
		
		for(auto& c : components)
		{
			Physical* phys = physSystem->get(c.second.ID());
			
			phys->position.x += c.second.velocity.x * dt;
			phys->position.y += c.second.velocity.y * dt;
		}
	}
	
	void MovableSystem::setPhysicalSystem(System<Physical>* ps)
	{
		physSystem = ps;
	}
}
