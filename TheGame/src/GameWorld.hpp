#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include "World/World.hpp"

#include "EntitySystem/Systems/AnimatedSystem.hpp"
#include "EntitySystem/Systems/BatchDrawSystem.hpp"
#include "EntitySystem/Systems/ControllableSystem.hpp"
#include "EntitySystem/Systems/DrawableSystem.hpp"
#include "EntitySystem/Systems/MovableSystem.hpp"
#include "EntitySystem/Systems/NameSystem.hpp"
#include "EntitySystem/Systems/NoisySystem.hpp"
#include "EntitySystem/Systems/PathfinderSystem.hpp"
#include "EntitySystem/Systems/PhysicalSystem.hpp"
#include "EntitySystem/Systems/ScriptableSystem.hpp"

#include "GameAssets.hpp"

namespace tg
{
	class GameWorld : public swift::World
	{
		public:
			GameWorld(const std::string& n, GameAssets* am);

			virtual void update(float dt);
			
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
			
		private:
			GameAssets* assets;
	};
}

#endif // GAMEWORLD_HPP
