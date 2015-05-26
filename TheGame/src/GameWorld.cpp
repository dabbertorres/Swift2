#include "GameWorld.hpp"

namespace tg
{
	GameWorld::GameWorld(const std::string& n, swift::AssetManager& am)
	:	World(n, 512),
		assets(am)
	{
		systems.add(swift::Component::Type::Animated, &animatedSys);
		systems.add(swift::Component::Type::BatchDrawable, &batchDrawSys);
		systems.add(swift::Component::Type::Controllable, &controlSys);
		systems.add(swift::Component::Type::Drawable, &drawSys);
		systems.add(swift::Component::Type::Movable, &moveSys);
		systems.add(swift::Component::Type::Noisy, &noisySys);
		systems.add(swift::Component::Type::Pathfinder, &pathSys);
		systems.add(swift::Component::Type::Physical, &physicalSys);
	}
	
	void GameWorld::update(float dt)
	{
		for(auto& s : systems)
		{
			s->update(dt);
		}
	}
	
	void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		target.draw(tilemap, states);
		
		static_cast<swift::BatchDrawSystem*>(systems.get<swift::BatchDrawable>())->draw(target, states, assets);
		static_cast<swift::DrawableSystem*>(systems.get<swift::Drawable>())->draw(target, states);
		static_cast<swift::AnimatedSystem*>(systems.get<swift::Animated>())->draw(target, states);
	}
}
