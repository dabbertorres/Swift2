#include "BatchDrawSystem.hpp"

#include "../Components/BatchDrawable.hpp"
#include "../Components/Physical.hpp"

#include "ResourceManager/AssetManager.hpp"

namespace swift
{
	BatchDrawSystem::BatchDrawSystem(AssetManager* am)
	:	assets(am)
	{}
	
	BatchDrawSystem::BatchDrawSystem(AssetManager* am, unsigned int res)
	:	System<BatchDrawable>(res),
		assets(am)
	{}
	
	void BatchDrawSystem::update(float)
	{
		for(auto& c : components)
		{
			const Physical& phys = c.getPhysical();
			
			c.sprite.setPosition({std::floor(phys.position.x), std::floor(phys.position.y)});
			
			c.sprite.setOrigin({std::floor(phys.size.x / 2.f), std::floor(phys.size.y / 2.f)});
			c.sprite.setRotation(phys.angle);
			c.sprite.setOrigin({0.f, 0.f});
		}
	}
	
	void BatchDrawSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for(auto& b : batches)
		{
			target.draw(*b, states);
		}
	}
	
	void BatchDrawSystem::addImpl(const BatchDrawable& c)
	{
		if(assets)
		{
			batches.insert(assets->getBatch(c.batch));
		}
	}
}
