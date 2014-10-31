#include "TestWorld.hpp"

namespace swift
{
	TestWorld::TestWorld(const std::string& n, const sf::Vector2i& s, AssetManager& a)
		:	World(n, s, a)
	{
	}

	TestWorld::~TestWorld()
	{
	}
	
	void TestWorld::update(float dt)
	{
		for(auto& e : entities)
		{
			moveSystem.update(*e, dt);
			physicalSystem.update(*e, dt);
			drawSystem.update(*e, dt);
		}
		
		std::vector<std::string> doneScripts;
		
		for(auto& s : scripts)
		{
			if(s.second->getWorld() != this)
				s.second->setWorld(*this);
			
			s.second->update();
			
			// check if script is done, if so, push it for deletion
			if(s.second->toDelete())
				doneScripts.push_back(s.first);
		}
		
		// remove all done scripts
		for(auto& s : doneScripts)
		{
			removeScript(s);
		}
	}

}
