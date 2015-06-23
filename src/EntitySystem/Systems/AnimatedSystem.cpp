#include "AnimatedSystem.hpp"

#include "../Components/Physical.hpp"

namespace swift
{
	AnimatedSystem::AnimatedSystem()
	:	physSystem(nullptr)
	{}
	
	void AnimatedSystem::update(float dt)
	{
		if(!physSystem)
		{
			return;
		}
		
		for(auto& c : components)
		{
			const Physical& phys = physSystem->get(c.second.ID());

			c.second.sprite.setPosition(std::floor(phys.position.x), std::floor(phys.position.y));

			c.second.sprite.setOrigin(std::floor(phys.size.x / 2.f), std::floor(phys.size.y / 2.f));
			c.second.sprite.setRotation(phys.angle);
			c.second.sprite.setOrigin(0.f, 0.f);
			
			c.second.sprite.setTextureRect(c.second.anims[c.second.currentAnim].update(dt));
		}
	}

	void AnimatedSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		/*std::sort(animateds.begin(), animateds.end(), [](const Entity* one, const Entity* two)
		{
			Physical* onePhys = one->get<Physical>();
			Physical* twoPhys = two->get<Physical>();
			
			if(onePhys->zIndex < twoPhys->zIndex)
			{
				return true;
			}
			else if(onePhys->zIndex == twoPhys->zIndex)
			{
				return onePhys->position.x < twoPhys->position.x || onePhys->position.y < twoPhys->position.y;
			}
			else
			{
				return false;
			}
		});*/
		
		for(auto& c : components)
		{
			target.draw(c.second.sprite, states);
		}
	}
	
	void AnimatedSystem::setPhysSystem(System<Physical>* ps)
	{
		physSystem = ps;
	}
}
