#include "ScriptManager.hpp"

#include "../ResourceManager/AssetManager.hpp"

namespace swift
{
	ScriptManager::ScriptManager(AssetManager& am)
	:	assets(am)
	{}
	
	void ScriptManager::update()
	{
		std::vector<std::string> doneScripts;

		for(auto& s : scripts)
		{
			s.second->update();

			// check if script is done, if so, push it for deletion
			if(s.second->toDelete())
				doneScripts.push_back(s.first);
		}

		// remove all done scripts
		for(auto& s : doneScripts)
		{
			remove(s);
		}
	}

	bool ScriptManager::add(const std::string& scriptFile)
	{
		if(scripts.find(scriptFile) == scripts.end())
		{
			scripts.emplace(scriptFile, assets.getScript(scriptFile));
			scripts[scriptFile]->start();
			
			return true;
		}
		else
			return false;
	}

	bool ScriptManager::remove(const std::string& scriptFile)
	{
		if(scripts.find(scriptFile) != scripts.end())
		{
			if(!scripts[scriptFile]->save("./data/saves/" + scriptFile.substr(scriptFile.find_last_of('/') + 1) + ".script"))
			{
				log << "[WARNING]: Could not save script: " << scriptFile << "!\n";
			}
			
			scripts[scriptFile]->reset();
			scripts.erase(scriptFile);
			return true;
		}
		else
			return false;
	}
	
	void ScriptManager::removeAll()
	{
		for(auto& s : scripts)
		{
			if(!s.second->save("./data/saves/" + s.first.substr(s.first.find_last_of('/') + 1) + ".script"))
			{
				log << "[WARNING]: Could not save script: " << s.first << "!\n";
			}
			
			s.second->reset();
		}
		
		scripts.clear();
	}
}
