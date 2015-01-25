#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include "../../src/World/World.hpp"

#include "../../src/EntitySystem/Systems/AnimatedSystem.hpp"
#include "../../src/EntitySystem/Systems/BatchDrawSystem.hpp"
#include "../../src/EntitySystem/Systems/ControllableSystem.hpp"
#include "../../src/EntitySystem/Systems/DrawableSystem.hpp"
#include "../../src/EntitySystem/Systems/MovableSystem.hpp"
#include "../../src/EntitySystem/Systems/NoisySystem.hpp"
#include "../../src/EntitySystem/Systems/PathfinderSystem.hpp"
#include "../../src/EntitySystem/Systems/PhysicalSystem.hpp"

namespace tg
{
	class GameWorld : public swift::World
	{
		public:
			GameWorld(const std::string& n, swift::AssetManager& am);

			virtual void update(float dt);
			virtual void draw(sf::RenderTarget& target, float e, sf::RenderStates states = sf::RenderStates::Default);

		private:
			swift::AnimatedSystem animSystem;
			swift::BatchDrawSystem batchSystem;
			swift::ControllableSystem controlSystem;
			swift::DrawableSystem drawSystem;
			swift::MovableSystem moveSystem;
			swift::PathfinderSystem pathSystem;
			swift::PhysicalSystem physicalSystem;
			
			swift::AssetManager& assets;
	};
}

#endif // GAMEWORLD_HPP
