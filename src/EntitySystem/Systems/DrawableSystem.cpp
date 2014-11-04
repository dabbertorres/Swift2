#include "DrawableSystem.hpp"

#include "../Components/Drawable.hpp"
#include "../Components/Physical.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace swift
{
	void DrawableSystem::update(Entity& entity, float /*dt*/)
	{
		if(entity.has<Drawable>() && entity.has<Physical>())
		{
			entity.get<Drawable>()->sprite.setPosition(entity.get<Physical>()->position);
		}
	}
	
	void DrawableSystem::draw(const Entity& entity, sf::RenderTarget& target, sf::RenderStates states) const
	{
		if(entity.has<Drawable>())
		{
			target.draw(const_cast<Entity&>(entity).get<Drawable>()->sprite, states);
		}
	}
}
