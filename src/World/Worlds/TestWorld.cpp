#include "TestWorld.hpp"

#include <fstream>

namespace swift
{
	TestWorld::TestWorld(const sf::Vector2i& s, AssetManager& am)
		:	World(s, am),
			tilemap(static_cast<sf::Vector2u>(s))
	{
		
	}

	void TestWorld::update(float dt)
	{
		for(auto& e : entities)
		{
			moveSystem.update(*e, dt);
			physicalSystem.update(*e, dt);
			if(e->has<Physical>())
			{
				// simple crappy world collision
				/*if(tilemap.getTileNum(static_cast<int>(phys->position.x / tilemap.getTileSize().x) + static_cast<int>(phys->position.y / tilemap.getTileSize().y) * tilemap.getSize().x) == 4 ||
					tilemap.getTileNum(static_cast<int>((phys->position.x + phys->size.x) / tilemap.getTileSize().x) + static_cast<int>((phys->position.y + phys->size.y) / tilemap.getTileSize().y) * tilemap.getSize().x) == 4 ||
					tilemap.getTileNum(static_cast<int>((phys->position.x) / tilemap.getTileSize().x) + static_cast<int>((phys->position.y + phys->size.y) / tilemap.getTileSize().y) * tilemap.getSize().x) == 4 ||
					tilemap.getTileNum(static_cast<int>((phys->position.x + phys->size.x) / tilemap.getTileSize().x) + static_cast<int>((phys->position.y) / tilemap.getTileSize().y) * tilemap.getSize().x) == 4)
				{
					phys->position = phys->previousPosition;
				}*/
			}
			drawSystem.update(*e, dt);
		}
	}

	bool TestWorld::load(const std::string& file)
	{
		std::ifstream fin;
		fin.open(file);
		
		if(fin.bad())
			return false;
		
		return true;
	}

	bool TestWorld::save(const std::string& file)
	{
		std::ofstream fout;
		fout.open(file);
		
		if(fout.bad())
			return false;
			
		return true;
	}
	
	void TestWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(tilemap, states);
		
		for(auto& e : entities)
		{
			drawSystem.draw(*e, target, states);
		}
	}
}
