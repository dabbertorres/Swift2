#include "ControllableSystem.hpp"

#include "../Components/Movable.hpp"

#include "Math/Math.hpp"

namespace swift
{
	ControllableSystem::ControllableSystem()
	:	moveSystem(nullptr)
	{}
	
	void ControllableSystem::update(float)
	{
		if(!moveSystem)
		{
			return;
		}
		
		for(auto& c : components)
		{
			sf::Vector2f moveDir = {0, 0};

			// set the direction based on keypresses
			if(c.second.moveLeft)
				moveDir += {-1, 0};

			if(c.second.moveRight)
				moveDir += {1, 0};

			if(c.second.moveUp)
				moveDir += {0, -1};

			if(c.second.moveDown)
				moveDir += {0, 1};
				
			Movable* mov = moveSystem->get(c.second.ID());

			// set the velocity based on the direction and the entity's move velocity
			mov->velocity = math::unit(moveDir) * mov->moveVelocity;
		}
	}
	
	void ControllableSystem::setMovableSystem(System<Movable>* ms)
	{
		moveSystem = ms;
	}
}
