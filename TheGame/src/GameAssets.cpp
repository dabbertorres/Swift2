#include "GameAssets.hpp"

#include "GameScript.hpp"

#include "ResourceManager/ResourceNotFound.hpp"

namespace tg
{
	swift::ScriptHandle GameAssets::getScript(const std::string& n)
	{
		auto s = scripts.find(n);
		if(s != scripts.end())
		{
			auto script = std::make_unique<GameScript>();
			script->loadFromFile(s->second);
			
			return script;
		}
		
		throw swift::ResourceNotFound("Could not find script: " + n);
	}
			
	bool GameAssets::loadScript(const gfs::Path& file)
	{
		std::string fileName = file.filename();
		
		scripts.emplace(fileName, file);
		
		swift::Logger::get() << "Script:\t" << fileName << '\n';
		
		return true;
	}
}
