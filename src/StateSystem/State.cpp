#include "State.hpp"

namespace swift
{
	State::State(sf::RenderWindow& win, AssetManager& am)
		: 	window(win),
			assets(am)
	{
	}

	State::~State()
	{
	}
	
	void State::updateScripts()
	{
		// check for scripts that are finished
		std::vector<std::vector<Script*>::iterator> deleteScripts;
		for(std::vector<Script*>::iterator it = activeScripts.begin(); it != activeScripts.end(); ++it)
		{
			if((*it)->toDelete())
				deleteScripts.push_back(it);
		}
		
		// remove scripts that are finished
		for(auto &it : deleteScripts)
		{
			activeScripts.erase(it);
		}
		
		// run scripts
		for(auto &s : activeScripts)
		{
			s->run();
		}
	}
}
