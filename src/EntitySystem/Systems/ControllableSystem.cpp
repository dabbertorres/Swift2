#include "ControllableSystem.hpp"

#include "../../Math/Math.hpp"

namespace swift
{
	// for system updates, I could, instead having if's every iteration of the for loop,
	// create a new vector of entities, conditionally copy to the new vector from 'entities'
	void ControllableSystem::update(const std::vector<Entity>& entities, float)
	{
		for(auto& e : entities)
		{
			if(e.has<Controllable>())
			{
				Controllable* cont = e.get<Controllable>();
				if(e.has<Movable>())
				{
					Movable* mov = e.get<Movable>();

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

					if(e.has<Animated>() && mov->velocity == sf::Vector2f{0, 0})
					{
						e.get<Animated>()->setAnimation("Idle");
					}
				}
			}
		}
	}
}
