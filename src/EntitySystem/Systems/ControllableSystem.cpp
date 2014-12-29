#include "ControllableSystem.hpp"

#include "../../Math/Math.hpp"

namespace swift
{
	void ControllableSystem::update(std::vector<Entity*>& entities, float)
	{
		for(auto& e : entities)
		{
			if(e->has<Controllable>() && e->has<Movable>())
			{
				Controllable* cont = e->get<Controllable>();
				Movable* mov = e->get<Movable>();
				
				sf::Vector2f moveDir = {0, 0};
				
				// set the direction based on keypresses
				if(cont->moveLeft)
					moveDir += {-1, 0};
				
				if(cont->moveRight)
					moveDir += {1, 0};
					
				if(cont->moveUp)
					moveDir += {0, -1};
				
				if(cont->moveDown)
					moveDir += {0, 1};
				
				// set the velocity based on the direction and the entity's move velocity
				mov->velocity = math::unit(moveDir) * mov->moveVelocity;
			}
		}
	}
}
