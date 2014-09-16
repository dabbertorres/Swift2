#include "MainWorld.hpp"

#include <fstream>

namespace swift
{
	MainWorld::MainWorld(const sf::Vector2i& s, AssetManager& am)
		:	World(s, am)
	{
	}

	void MainWorld::update(float dt)
	{
		for(auto& e : getEntities())
		{
			moveSystem.update(e, dt);
			physicalSystem.update(e, dt);
			if(e.has<Physical>())
			{
				Physical* phys = e.get<Physical>();
				// check x position
				if(phys->position.x < 0)
					phys->position.x = 0;
				else if(phys->position.x + phys->size.x > size.x)
					phys->position.x = size.x - phys->size.x;
				// check y position
				if(phys->position.y < 0)
					phys->position.y = 0;
				else if(phys->position.y + phys->size.y > size.y)
					phys->position.y = size.y - phys->size.y;
			}
			drawSystem.update(e, dt);
		}
	}

	void MainWorld::draw(sf::RenderTarget& target)
	{
		for(auto& e : getEntities())
		{
			drawSystem.draw(e, target);
		}
	}
	
	void MainWorld::draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		for(auto& e : getEntities())
		{
			drawSystem.draw(e, target, states);
		}
	}

	void MainWorld::load(const std::string& file)
	{
		std::ifstream fin;
		fin.open(file);

		// setup entity
		Entity& player = addEntity();
		player.add<Drawable>();
		player.add<Physical>();
		player.add<Movable>();

		player.get<Drawable>()->sprite.setTexture(assets.getTexture("./data/textures/guy.png"));

		player.get<Physical>()->position = {400, 300};
		player.get<Physical>()->size = assets.getTexture("./data/textures/guy.png").getSize();
		player.get<Movable>()->moveVelocity = 100;
	}

	void MainWorld::save(const std::string& file)
	{
		std::ofstream fout;
		fout.open(file);
	}
}
