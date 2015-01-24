#include "AnimatedSystem.hpp"

namespace swift
{
	void AnimatedSystem::update(std::vector<Entity*>& entities, float dt)
	{
		for(auto& e : entities)
		{
			if(e->has<Animated>() && e->has<Physical>())
			{
				Physical* phys = e->get<Physical>();
				Animated* anim = e->get<Animated>();

				anim->sprite.setPosition(std::floor(phys->position.x), std::floor(phys->position.y));

				anim->sprite.setOrigin(std::floor(phys->size.x / 2.f), std::floor(phys->size.y / 2.f));
				anim->sprite.setRotation(phys->angle);
				anim->sprite.setOrigin(0.f, 0.f);
				
				anim->sprite.setTextureRect(anim->anims[anim->currentAnim].update(dt));
			}
		}
	}

	void AnimatedSystem::draw(std::vector<Entity*>& entities, float, sf::RenderTarget& target, sf::RenderStates states) const
	{
		std::vector<Entity*> animateds;
		
		for(auto& e : entities)
		{
			if(e->has<Animated>() && e->has<Physical>())
				animateds.push_back(e);
		}
		
		std::sort(animateds.begin(), animateds.end(), [](Entity* one, Entity* two)
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
		
		for(auto& a : animateds)
		{
			/*if(d->has<Movable>())
			{
				Movable* m = d->get<Movable>();
				sf::Sprite* s = &d->get<Drawable>()->sprite;
				s->setPosition(s->getPosition().x + m->velocity.x * e, s->getPosition().y + m->velocity.y * e);
			}*/
			target.draw(a->get<Animated>()->sprite, states);
		}
	}
}
