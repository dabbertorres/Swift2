#ifndef NOISYSYSTEM_HPP
#define NOISYSYSTEM_HPP

#include "../System.hpp" // Base class: swift::System

#include "../Entity.hpp"

#include "../../SoundSystem/SoundPlayer.hpp"
#include "../../ResourceManager/AssetManager.hpp"

namespace swift
{
	class NoisySystem : public System
	{
		public:
			NoisySystem(SoundPlayer& sp, AssetManager& am);
			virtual void update(std::vector<Entity*>& entities, float dt);

		private:
			SoundPlayer& soundPlayer;
			AssetManager& assets;
	};
}

#endif // NOISYSYSTEM_HPP
