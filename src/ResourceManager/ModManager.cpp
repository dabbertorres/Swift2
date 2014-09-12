#include "ModManager.hpp"

#include <iostream>

#include "../Settings/Settings.hpp"

namespace swift
{
	ModManager::ModManager()
	{
	}

	ModManager::~ModManager()
	{
	}

	bool ModManager::loadMods(const std::string& f)
	{
		DIR* dir = nullptr;
		struct dirent* entry = nullptr;

		dir = opendir(f.c_str());

		// error handling
		if(dir == nullptr)
		{
			log << "Unable to open mod folder: " << f << "\n";
			return false;
		}

		while((entry = readdir(dir)))
		{
			if(entry == nullptr)
			{
				log << "Unable to read mod folder: " << f << "\n";
				return false;
			}

			// if the entry is a directory, but is not the current or parent directory
			if(entry->d_type == DT_DIR && !(std::string(entry->d_name).compare(".") == 0 || std::string(entry->d_name).compare("..") == 0))
			{
				std::ifstream fin;
				std::string name;
				std::string version;
				std::string author;
				std::string description;

				swift::Settings info;
				info.loadFile(f + '/' + std::string(entry->d_name) + "/info.txt");
				
				bool nameError = info.get("name", name);
				bool versionError = info.get("version", version);
				bool authorError = info.get("author", author);
				bool descriptionError = info.get("description", description);
				
				if(!(nameError || versionError || authorError || descriptionError))
				{
					log << "Ill formed info.txt for mod \"" << entry->d_name << "\", not loading.\n";
					continue;
				}
				
				mods.emplace(name, ModPair());
				mods[name].mod.setName(name);
				mods[name].mod.setVersion(version);
				mods[name].mod.setAuthor(author);
				mods[name].mod.setDescription(description);
				
				log << "\nLoading mod: " << name << '\n';
				log << "Version: " << version << '\n';
				log << "By: " << author << '\n';
				log << description << '\n';
				loadMod(f + '/' + std::string(entry->d_name), mods[name].mod);
			}
		}

		closedir(dir);

		return true;
	}

	const std::map<std::string, ModManager::ModPair>& ModManager::getMods() const
	{
		return mods;
	}
	
	std::map<std::string, ModManager::ModPair>::iterator ModManager::getMod(const std::string& n)
	{
		return mods.find(n);
	}

	bool ModManager::loadMod(const std::string& f, Mod& mod)
	{
		DIR* dir = nullptr;
		struct dirent* entry = nullptr;

		dir = opendir(f.c_str());

		// error handling
		if(dir == nullptr)
		{
			log << "Unable to open resource folder!\n";
			return false;
		}

		while((entry = readdir(dir)))
		{
			if(entry == nullptr)
			{
				log << "Unable to read resource folder!\n";
				return false;
			}

			// if the entry is a directory, but is not the current or parent directory
			if(entry->d_type == DT_DIR && !(std::string(entry->d_name).compare(".") == 0 || std::string(entry->d_name).compare("..") == 0))
			{
				loadMod(f + '/' + std::string(entry->d_name), mod);
			}
			else if(entry->d_type == DT_REG)
			{
				log << "\tFound mod file: " << f + '/' + std::string(entry->d_name) << '\n';
				mod.addFile(f + '/' + std::string(entry->d_name));
			}
		}

		closedir(dir);

		return true;
	}
}
