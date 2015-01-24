#include "GameAssets.hpp"

#include "GameScript.hpp"

namespace tg
{
	GameAssets::GameAssets()
	{
	}

	GameAssets::~GameAssets()
	{
	}
	
	bool GameAssets::loadScript(const std::string& file)
	{
		scripts.emplace(file, new GameScript());

		if(!scripts[file]->loadFromFile(file))
		{
			swift::log << "Unable to load " << file << " as a script.\n";

			// delete new'd script
			auto it = scripts.end();
			it--;
			delete it->second;

			scripts.erase(file);
			return false;
		}

		swift::log << "Script:\t" << file << '\n';

		scripts[file]->load("./data/saves/" + file.substr(file.find_last_of('/') + 1) + ".script");
		
		return true;
	}
}
