#include "GameAssets.hpp"

#include "GameScript.hpp"

namespace tg
{
	bool GameAssets::loadScript(const gfs::Path& file)
	{
		std::string fileName = file.filename();

		scripts.emplace(fileName, new GameScript());

		if(!scripts[fileName]->loadFromFile(file))
		{
			swift::Logger::get() << "Unable to load " << file << " as a script.\n";

			// delete new script
			delete scripts[fileName];

			scripts.erase(fileName);
			return false;
		}

		swift::Logger::get() << "Script:\t" << fileName << '\n';

		return true;
	}
}
