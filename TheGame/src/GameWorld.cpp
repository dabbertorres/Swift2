#include "GameWorld.hpp"

namespace tg
{
	GameWorld::GameWorld(const std::string& n, swift::AssetManager& am)
	:	World(n),
		assets(am)
	{
	}
	
	void GameWorld::update(float dt)
	{
		controlSystem.update(entities, dt);
		moveSystem.update(entities, dt);
		pathSystem.update(entities, dt);
		physicalSystem.update(entities, dt);
		
		animSystem.update(entities, dt);
		drawSystem.update(entities, dt);
		batchSystem.update(entities, dt);
	}
	
	void GameWorld::draw(sf::RenderTarget& target, float e, sf::RenderStates states)
	{
		target.draw(tilemap, states);
		animSystem.draw(entities, e, target, states);
		drawSystem.draw(entities, e, target, states);
		batchSystem.draw(entities, e, target, states, assets);
	}
}
