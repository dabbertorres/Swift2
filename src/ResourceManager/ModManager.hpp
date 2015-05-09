#ifndef MODMANAGER_HPP
#define MODMANAGER_HPP

#include <fstream>
#include <string>
#include <map>

#include <dirent.h>

#include "Mod.hpp"

namespace swift
{
	class ModManager
	{
		public:
			ModManager() = default;
			~ModManager() = default;

			bool loadMods(const std::string& f);
			
			const std::map<std::string, Mod>& getMods() const;

			std::map<std::string, Mod>::iterator getMod(const std::string& n);

			// for checking if a mod was found or not
			const std::map<std::string, Mod>::iterator NOT_FOUND = mods.end();

		private:
			bool loadMod(const std::string& f, Mod& mod);

			std::map<std::string, Mod> mods;
	};
}

#endif // MODMANAGER_HPP
