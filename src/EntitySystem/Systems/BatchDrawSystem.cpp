#include "BatchDrawSystem.hpp"

#include "../Components/BatchDrawable.hpp"
#include "../Components/Physical.hpp"

#include "ResourceManager/AssetManager.hpp"
#include "ResourceManager/ResourceNotFound.hpp"

namespace swift
{
	BatchDrawSystem::BatchDrawSystem(AssetManager* am)
	:	physSystem(nullptr),
		assets(am)
	{}
	
	void BatchDrawSystem::update(float)
	{
		if(!physSystem)
		{
			return;
		}
		
		for(auto& c : components)
		{
			const Physical& phys = physSystem->get(c.second.ID());
			
			c.second.sprite.setPosition({std::floor(phys.position.x), std::floor(phys.position.y)});
			
			c.second.sprite.setOrigin({std::floor(phys.size.x / 2.f), std::floor(phys.size.y / 2.f)});
			c.second.sprite.setRotation(phys.angle);
			c.second.sprite.setOrigin({0.f, 0.f});
		}
	}
	
	void BatchDrawSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for(auto& b : batches)
		{
			target.draw(*b, states);
		}
	}
	
	void BatchDrawSystem::setPhysSystem(System<Physical>* ps)
	{
		physSystem = ps;
	}
	
	void BatchDrawSystem::addImpl(const BatchDrawable& c)
	{
		if(assets)
		{
			try
			{
				batches.insert(&assets->getBatch(c.batch));
			}
			catch(const ResourceNotFound& rnf)
			{
				Logger::get() << rnf.what() << '\n';
			}
		}
	}
}
