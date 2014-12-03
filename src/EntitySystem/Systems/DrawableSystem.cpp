#include "DrawableSystem.hpp"

#include "../Components/Drawable.hpp"
#include "../Components/Physical.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace swift
{
	void DrawableSystem::update(const std::vector<Entity*>& entities, float /*dt*/)
	{
		for(auto& e : entities)
		{
			if(e->has<Drawable>() && e->has<Physical>())
			{
				e->get<Drawable>()->sprite.setPosition(e->get<Physical>()->position);
			}
		}
	}

	void DrawableSystem::draw(const std::vector<Entity*>& entities, sf::RenderTarget& target, sf::RenderStates states) const
	{
		for(auto& e : entities)
		{
			if(e->has<Drawable>())
			{
				target.draw(e->get<Drawable>()->sprite, states);
			}
		}
	}
}
