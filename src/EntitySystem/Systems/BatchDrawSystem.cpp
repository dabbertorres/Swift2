#include "BatchDrawSystem.hpp"

#include "../Components/BatchDrawable.hpp"
#include "../Components/Physical.hpp"

#include "../../ResourceManager/AssetManager.hpp"

#include <unordered_set>

namespace swift
{
	void BatchDrawSystem::update(std::vector<Entity*>& entities, float)
	{
		for(auto& e : entities)
		{
			if(e->has<BatchDrawable>() && e->has<Physical>())
			{
				Physical* phys = e->get<Physical>();
				BatchDrawable* draw = e->get<BatchDrawable>();
				
				draw->sprite.setPosition({std::floor(phys->position.x), std::floor(phys->position.y)});
				
				draw->sprite.setOrigin({std::floor(phys->size.x / 2.f), std::floor(phys->size.y / 2.f)});
				draw->sprite.setRotation(phys->angle);
				draw->sprite.setOrigin({0.f, 0.f});
			}
		}
	}

	void BatchDrawSystem::draw(std::vector<Entity*>& entities, float, sf::RenderTarget& target, sf::RenderStates states, AssetManager& assets) const
	{
		std::unordered_set<std::string> batches;
		
		for(auto& e : entities)
		{
			if(e->has<BatchDrawable>())
				batches.insert(e->get<BatchDrawable>()->batch);
		}
		
		for(auto& b : batches)
			target.draw(*assets.getBatch(b), states);
	}
}
