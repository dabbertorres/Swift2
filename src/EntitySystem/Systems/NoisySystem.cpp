#include "NoisySystem.hpp"

#include "../Components/Physical.hpp"

namespace swift
{
	SoundPlayer* NoisySystem::soundPlayer = nullptr;
	AssetManager* NoisySystem::assets = nullptr;
	
	void NoisySystem::update(float)
	{
		for(auto& c : components)
		{
			const Physical& phys = c.getPhysical();

			if(c.shouldPlay)
			{
				soundPlayer->newSound(*assets->getSoundBuffer(c.soundFile), {phys.position.x, phys.position.y, 0}, false);
				c.shouldPlay = false;
			}
		}
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
