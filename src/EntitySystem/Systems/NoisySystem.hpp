#ifndef NOISYSYSTEM_HPP
#define NOISYSYSTEM_HPP

#include "../System.hpp"

#include "../Components/Noisy.hpp"

#include "../../SoundSystem/SoundPlayer.hpp"
#include "../../ResourceManager/AssetManager.hpp"

namespace swift
{
	class NoisySystem : public System<Noisy>
	{
		public:
			virtual void update(float dt);
			
			static void setSoundPlayer(SoundPlayer& sp);
			static void setAssetManager(AssetManager& am);

		private:
			static SoundPlayer* soundPlayer;
			static AssetManager* assets;
	};
}

#endif // NOISYSYSTEM_HPP
