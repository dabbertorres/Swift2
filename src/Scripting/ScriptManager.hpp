#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP

#include <map>

#include "../Logger/Logger.hpp"

#include "Script.hpp"

namespace swift
{
	class AssetManager;
	
	class ScriptManager
	{
		public:
			ScriptManager(AssetManager& am);
			~ScriptManager() = default;

			void update();

			bool add(const std::string& scriptFile);
			bool remove(const std::string& scriptFile);
			void removeAll();

		private:
			std::map<std::string, Script*> scripts;
			AssetManager& assets;
	};
}

#endif // SCRIPTMANAGER_HPP
