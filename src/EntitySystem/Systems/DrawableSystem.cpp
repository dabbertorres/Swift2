#include "DrawableSystem.hpp"

#include "../Components/Drawable.hpp"
#include "../Components/Physical.hpp"

namespace swift
{
	void DrawableSystem::update(Entity& entity, float /*dt*/)
	{
		if(entity.has<Drawable>() && entity.has<Physical>())
		{
			entity.get<Drawable>()->sprite.setPosition(entity.get<Physical>()->position);
		}
	}
	
	void DrawableSystem::draw(Entity& entity, sf::RenderTarget& target)
	{
		if(entity.has<Drawable>() && entity.has<Physical>())
		{
			target.draw(entity.get<Drawable>()->sprite);
		}
	}
	
	void DrawableSystem::draw(Entity& entity, sf::RenderTarget& target, sf::RenderStates states)
	{
		if(entity.has<Drawable>() && entity.has<Physical>())
		{
			target.draw(entity.get<Drawable>()->sprite, states);
		}
	}
}
