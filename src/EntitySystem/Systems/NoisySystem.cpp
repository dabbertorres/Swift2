#include "NoisySystem.hpp"

#include "../Components/Physical.hpp"

namespace swift
{
	SoundPlayer* NoisySystem::soundPlayer = nullptr;
	AssetManager* NoisySystem::assets = nullptr;
	
	NoisySystem::NoisySystem()
	:	physSystem(nullptr)
	{}
	
	void NoisySystem::update(float)
	{
		if(!physSystem)
		{
			return;
		}
		
		for(auto& c : components)
		{
			const Physical* phys = physSystem->get(c.second.ID());

			if(c.second.shouldPlay)
			{
				soundPlayer->newSound(assets->getSound(c.second.soundFile), {phys->position.x, phys->position.y, 0}, false);
				c.second.shouldPlay = false;
			}
		}
	}
	
	void NoisySystem::setPhysSystem(System<Physical>* ps)
	{
		physSystem = ps;
	}
	
	void NoisySystem::setSoundPlayer(SoundPlayer& sp)
	{
		soundPlayer = &sp;
	}
	
	void NoisySystem::setAssetManager(AssetManager& am)
	{
		assets = &am;
	}
}
