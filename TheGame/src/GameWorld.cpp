#include "GameWorld.hpp"

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

namespace tg
{
	GameWorld::GameWorld(const std::string& n, GameAssets* am)
	:	World(n, 512),
		assets(am)
	{
		systems.add(new swift::AnimatedSystem());
		systems.add(new swift::BatchDrawSystem(assets));
		systems.add(new swift::ControllableSystem());
		systems.add(new swift::DrawableSystem());
		systems.add(new swift::MovableSystem());
		systems.add(new swift::NoisySystem());
		systems.add(new swift::PathfinderSystem());
		systems.add(new swift::PhysicalSystem());
	}
	
	void GameWorld::update(float dt)
	{
		for(auto& s : systems)
		{
			s.second->update(dt);
		}
	}
	
	void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		target.draw(tilemap, states);
		
		static_cast<swift::BatchDrawSystem*>(systems.get<swift::BatchDrawable>())->draw(target, states);
		static_cast<swift::DrawableSystem*>(systems.get<swift::Drawable>())->draw(target, states);
		static_cast<swift::AnimatedSystem*>(systems.get<swift::Animated>())->draw(target, states);
	}
}
