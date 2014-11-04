#include "NoisySystem.hpp"

namespace swift
{
	NoisySystem::NoisySystem(SoundPlayer& sp, AssetManager& am)
		:	soundPlayer(sp),
			assets(am)
	{}
	
	void NoisySystem::update(Entity& entity, float)
	{
		if(entity.has<Noisy>() && entity.has<Physical>())
		{
			Noisy* noisy = entity.get<Noisy>();
			Physical* physical = entity.get<Physical>();
			
			if(noisy->shouldPlay && !noisy->isPlaying)
			{
				soundPlayer.newSound(assets.getSoundBuffer(noisy->soundFile), {physical->position.x, physical->position.y, 0}, false);
				noisy->isPlaying = true;
				noisy->shouldPlay = false;
			}
		}
	}
}
