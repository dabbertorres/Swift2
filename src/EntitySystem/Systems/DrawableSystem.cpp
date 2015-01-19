#include "DrawableSystem.hpp"

#include "../Components/Drawable.hpp"
#include "../Components/Physical.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace swift
{
	void DrawableSystem::update(std::vector<Entity*>& entities, float /*dt*/)
	{
		for(auto& e : entities)
		{
			if(e->has<Drawable>() && e->has<Physical>())
			{
				Physical* phys = e->get<Physical>();
				Drawable* draw = e->get<Drawable>();
				
				draw->sprite.setPosition(std::floor(phys->position.x), std::floor(phys->position.y));
				
				draw->sprite.setOrigin(std::floor(phys->size.x / 2.f), std::floor(phys->size.y / 2.f));
				draw->sprite.setRotation(phys->angle);
				draw->sprite.setOrigin(0.f, 0.f);
			}
		}
	}

	void DrawableSystem::draw(std::vector<Entity*>& entities, float e, sf::RenderTarget& target, sf::RenderStates states) const
	{
		std::vector<Entity*> drawables;
		
		for(auto& e : entities)
		{
			if(e->has<Drawable>() && e->has<Physical>())
				drawables.push_back(e);
		}
		
		std::sort(drawables.begin(), drawables.end(), [](Entity* one, Entity* two)
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
		});
		
		for(auto& d : drawables)
		{
			/*if(d->has<Movable>())
			{
				Movable* m = d->get<Movable>();
				sf::Sprite* s = &d->get<Drawable>()->sprite;
				s->setPosition(s->getPosition().x + m->velocity.x * e, s->getPosition().y + m->velocity.y * e);
			}*/
			target.draw(d->get<Drawable>()->sprite, states);
		}
	}
}
