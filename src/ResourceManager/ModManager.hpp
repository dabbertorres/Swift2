#ifndef MODMANAGER_HPP
#define MODMANAGER_HPP

#include <fstream>
#include <string>
#include <map>

#include <dirent.h>

#include "../Logger/Logger.hpp"

#include "Mod.hpp"

namespace swift
{
	class ModManager
	{
		private:
			struct ModPair;

		public:
			ModManager();
			~ModManager();

			bool loadMods(const std::string& f);
			
			const std::map<std::string, ModPair>& getMods() const;

			std::map<std::string, ModPair>::iterator getMod(const std::string& n);

			// for checking if a mod was found or not
			const std::map<std::string, ModPair>::iterator NOT_FOUND = mods.end();

		private:
			bool loadMod(const std::string& f, Mod& mod);

			struct ModPair
			{
				ModPair()
					: mod(), active(false)
				{}
				ModPair(const std::string& n, const std::string& v, const std::string& a)
					: mod(n, v, a), active(false)
				{}
				Mod mod;
				bool active;
			};

			std::map<std::string, ModPair> mods;
	};
}

#endif // MODMANAGER_HPP
