#include "DrawableSystem.hpp"

#include "../Components/Drawable.hpp"
#include "../Components/Physical.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace swift
{
	DrawableSystem::DrawableSystem()
	:	physSystem(nullptr)
	{}
	
	void DrawableSystem::update(float)
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
		}
	}

	void DrawableSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		/*std::sort(drawables.begin(), drawables.end(), [](const Entity* one, const Entity* two)
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
	
	void DrawableSystem::setPhysSystem(System<Physical>* ps)
	{
		physSystem = ps;
	}
}
