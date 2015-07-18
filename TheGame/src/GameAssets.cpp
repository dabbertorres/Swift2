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
}
