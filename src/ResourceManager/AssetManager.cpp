#include "AssetManager.hpp"

#include <iostream>

namespace swift
{
	AssetManager::AssetManager()
	{
		smooth = false;
	}

	AssetManager::~AssetManager()
	{
		for(auto& t : textures)
			delete t.second;
		
		//for(auto& s : skeletons)
		//	delete s.second;
		
		for(auto& s : soundBuffers)
			delete s.second;
			
		for(auto& m : music)
			delete m.second;
		
		for(auto& f : fonts)
			delete f.second;
		
		for(auto& s : scripts)
			delete s.second;
	}

	bool AssetManager::loadResourceFolder(const std::string& folder)
	{
		DIR* dir = nullptr;
		struct dirent* entry = nullptr;

		dir = opendir(folder.c_str());

		// error handling
		if(dir == nullptr)
		{
			log << "Unable to open resource folder: " << folder << "\n";
			return false;
		}

		while((entry = readdir(dir)))
		{
			if(entry == nullptr)
			{
				log << "Unable to read resource folder: " << folder << "\n";
				return false;
			}

			// if the entry is a directory, but is not the current or parent directory
			if(entry->d_type == DT_DIR && !(std::string(entry->d_name).compare(".") == 0 || std::string(entry->d_name).compare("..") == 0))
			{
				loadResourceFolder(folder + '/' + std::string(entry->d_name));	// recursive on child directory
			}
			// entry is a file
			else if(entry->d_type == DT_REG)
			{
				loadResource(folder + '/' + std::string(entry->d_name));
			}
		}

		closedir(dir);
		
		return true;
	}
	
	bool AssetManager::loadMod(const Mod& mod)
	{
		bool returnVar = true;
		
		for(auto &f : mod.getFiles())
		{
			bool temp = true;
			temp = loadResource(f);
			if(temp == false)
			{
				log << "ERROR: In " << mod.getName() << ", could not load " << f << '\n';
				returnVar = false;
			}
		}
		
		return returnVar;
	}

	void AssetManager::clean()
	{
		textures.clear();
		//skeletons.clear();
		soundBuffers.clear();
		music.clear();
		fonts.clear();
		scripts.clear();
	}

	void AssetManager::setSmooth(bool s)
	{
		smooth = s;
		for(auto &t : textures)
		{
			t.second->setSmooth(smooth);
		}
	}

	sf::Texture& AssetManager::getTexture(const std::string& n)
	{
		return *textures.find(n)->second;
	}
	
	/*Bitmask& AssetManager::getBitmask(const std::string& n)
	{
		return *bitmasks.find(n)->second;
	}*/
	
	/*Skeleton& AssetManager::getSkeleton(const std::string& n)
	{
		return *skeletons.find(n)->second;
	}*/
	
	sf::SoundBuffer& AssetManager::getSoundBuffer(const std::string& n)
	{
		return *soundBuffers.find(n)->second;
	}
	
	sf::Music& AssetManager::getSong(const std::string& n)
	{
		return *music.find(n)->second;
	}
	
	sf::Font& AssetManager::getFont(const std::string& n)
	{
		return *fonts.find(n)->second;
	}
	
	Script& AssetManager::getScript(const std::string& n)
	{
		return *scripts.find(n)->second;
	}

	bool AssetManager::loadResource(const std::string& file)
	{
		// this if chain checks what folder the file is in
		if(file.find("/textures/") != std::string::npos)
		{
			// I can construct things in place using a piecewise_construct combined with a std::<container_type>.emplace(Args&& args ...)
			textures.emplace(file, new sf::Texture());

			if(!textures[file]->loadFromFile(file))
			{
				log << "Unable to load " << file << " as a texture.\n";
				textures.erase(file);
				return false;
			}
			textures[file]->setSmooth(smooth);

			log << "Texture: " << file << '\n';
		}
		else if(file.find("/skeletons/") != std::string::npos)
		{
			// create a skeleton
		}
		else if(file.find("/sounds/") != std::string::npos)
		{
			soundBuffers.emplace(file, new sf::SoundBuffer());

			if(!soundBuffers[file]->loadFromFile(file))
			{
				log << "Unable to load " << file << " as a sound.\n";
				soundBuffers.erase(file);
				return false;
			}

			log << "Sound: \t " << file << '\n';
		}
		else if(file.find("/music/") != std::string::npos)
		{
			music.emplace(file, new sf::Music());

			if(!music[file]->openFromFile(file))
			{
				log << "Unable to open " << file << " as a music file.\n";
				music.erase(file);
				return false;
			}

			log << "Music: \t " << file << '\n';
		}
		else if(file.find("/fonts/") != std::string::npos)
		{
			fonts.emplace(file, new sf::Font());

			if(!fonts[file]->loadFromFile(file))
			{
				log << "Unable to load " << file << " as a font.\n";
				fonts.erase(file);
				return false;
			}

			log << "Font: \t " << file << '\n';
		}
		else if(file.find("/scripts/") != std::string::npos)
		{
			scripts.emplace(file, new Script());
			
			if(!scripts[file]->loadFromFile(file))
			{
				log << "Unable to load " << file << " as a script.\n";
				scripts.erase(file);
				return false;
			}
		}
		else if(file.find(".txt") != std::string::npos)
		{
			// ignore *.txt files, but don't throw a warning/error
			log << "Ignoring " << file << '\n';
		}
		else
		{
			log << "WARNING: " << file << " is an unknown resource type.\n";
			return false;
		}
		return true;
	}
}
