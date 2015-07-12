#include "GameWorld.hpp"

namespace tg
{
	GameWorld::GameWorld(const std::string& n, GameAssets* am)
	:	World(n, 512),
		assets(am)
	{
		systems.add(swift::Component::Type::Animated, new swift::AnimatedSystem());
		systems.add(swift::Component::Type::BatchDrawable, new swift::BatchDrawSystem(assets));
		systems.add(swift::Component::Type::Controllable, new swift::ControllableSystem());
		systems.add(swift::Component::Type::Drawable, new swift::DrawableSystem());
		systems.add(swift::Component::Type::Movable, new swift::MovableSystem());
		systems.add(swift::Component::Type::Noisy, new swift::NoisySystem());
		systems.add(swift::Component::Type::Pathfinder, new swift::PathfinderSystem());
		systems.add(swift::Component::Type::Physical, new swift::PhysicalSystem());
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
