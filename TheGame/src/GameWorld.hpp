#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include "../../src/World/World.hpp"

#include "../../src/EntitySystem/Systems/AnimatedSystem.hpp"
#include "../../src/EntitySystem/Systems/BatchDrawSystem.hpp"
#include "../../src/EntitySystem/Systems/ControllableSystem.hpp"
#include "../../src/EntitySystem/Systems/DrawableSystem.hpp"
#include "../../src/EntitySystem/Systems/MovableSystem.hpp"
#include "../../src/EntitySystem/Systems/NameSystem.hpp"
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
			
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
			
		private:
			swift::AssetManager& assets;
			
			// list of systems declared on the stack
			swift::AnimatedSystem animatedSys;
			swift::BatchDrawSystem batchDrawSys;
			swift::ControllableSystem controlSys;
			swift::DrawableSystem drawSys;
			swift::MovableSystem moveSys;
			swift::NameSystem nameSys;
			swift::NoisySystem noisySys;
			swift::PathfinderSystem pathSys;
			swift::PhysicalSystem physicalSys;
	};
}

#endif // GAMEWORLD_HPP
