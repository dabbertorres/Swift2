#include "BatchDrawSystem.hpp"

#include "../Components/BatchDrawable.hpp"
#include "../Components/Physical.hpp"

#include "../../ResourceManager/AssetManager.hpp"

namespace swift
{
	BatchDrawSystem::BatchDrawSystem(unsigned int res)
	:	System<BatchDrawable>(res)
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

	void BatchDrawSystem::draw(sf::RenderTarget& target, sf::RenderStates states, AssetManager& assets) const
	{
		for(auto& b : batches)
		{
			target.draw(*assets.getBatch(b), states);
		}
	}
	
	void BatchDrawSystem::addImpl(const BatchDrawable& c)
	{
		batches.insert(c.batch);
	}
}
