#ifndef NOISYSYSTEM_HPP
#define NOISYSYSTEM_HPP

#include "../System.hpp"

#include "../Components/Noisy.hpp"
#include "../Components/Physical.hpp"

#include "SoundSystem/SoundPlayer.hpp"
#include "ResourceManager/AssetManager.hpp"

namespace swift
{
	class NoisySystem : public System<Noisy>
	{
		public:
			NoisySystem();
			
			virtual void update(float dt);
			
			void setPhysSystem(System<Physical>* ps);
			
			static void setSoundPlayer(SoundPlayer& sp);
			static void setAssetManager(AssetManager& am);

		private:
			static SoundPlayer* soundPlayer;
			static AssetManager* assets;
			
			System<Physical>* physSystem;
	};
}

#endif // NOISYSYSTEM_HPP
