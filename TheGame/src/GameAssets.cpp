#include "GameAssets.hpp"

#include "GameScript.hpp"

namespace tg
{
	GameAssets::GameAssets(const std::string& rp)
		:	resPath(rp)
	{
	}

	GameAssets::~GameAssets()
	{
	}

	bool GameAssets::loadScript(const std::string& file)
	{
		std::string fileName = file.substr(file.find_last_of('/') + 1);

		scripts.emplace(fileName, new GameScript());

		if(!scripts[fileName]->loadFromFile(file))
		{
			swift::log << "Unable to load " << file << " as a script.\n";

			// delete new'd script
			delete scripts[fileName];

			scripts.erase(fileName);
			return false;
		}

		swift::log << "Script:\t" << fileName << '\n';

		scripts[fileName]->load(resPath + "../data/saves/" + fileName + ".script");

		return true;
	}
}
