#include "ControllableSystem.hpp"

#include "../Components/Movable.hpp"

#include "../../Math/Math.hpp"

namespace swift
{
	ControllableSystem::ControllableSystem(unsigned int res)
	:	System<Controllable>(res)
	{}
	
	void ControllableSystem::update(float)
	{
		for(auto& c : components)
		{
			sf::Vector2f moveDir = {0, 0};

			// set the direction based on keypresses
			if(c.moveLeft)
				moveDir += {-1, 0};

			if(c.moveRight)
				moveDir += {1, 0};

			if(c.moveUp)
				moveDir += {0, -1};

			if(c.moveDown)
				moveDir += {0, 1};
				
			Movable& mov = c.getMovable();

			// set the velocity based on the direction and the entity's move velocity
			mov.velocity = math::unit(moveDir) * mov.moveVelocity;
		}
	}
}
