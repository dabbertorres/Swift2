#include "NoisySystem.hpp"

namespace swift
{
	NoisySystem::NoisySystem(SoundPlayer& sp, AssetManager& am)
		:	soundPlayer(sp),
		    assets(am)
	{}

	void NoisySystem::update(std::vector<Entity*>& entities, float)
	{
		for(auto& e : entities)
		{
			if(e->has<Noisy>() && e->has<Physical>())
			{
				Noisy* noisy = e->get<Noisy>();
				Physical* physical = e->get<Physical>();

				if(noisy->shouldPlay)
				{
					soundPlayer.newSound(*assets.getSoundBuffer(noisy->soundFile), {physical->position.x, physical->position.y, 0}, false);
					noisy->shouldPlay = false;
				}
			}
		}
	}
}
