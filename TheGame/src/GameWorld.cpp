#include "GameWorld.hpp"

namespace tg
{
	GameWorld::GameWorld(const std::string& n, swift::AssetManager& am)
	:	World(n),
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
	
	void GameWorld::draw(sf::RenderTarget& target, float e, sf::RenderStates states)
	{
		target.draw(tilemap, states);
		
		systems.get<swift::BatchDrawSystem>().draw(e, target, states, assets);
		systems.get<swift::DrawableSystem>().draw(e, target, states);
		systems.get<swift::AnimatedSystem>().draw(e, target, states);
	}
}
