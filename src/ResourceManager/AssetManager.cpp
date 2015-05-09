#include "AssetManager.hpp"

#include <dirent.h>

namespace swift
{
	AssetManager::AssetManager()
	{
		smooth = false;
		sf::err().rdbuf(nullptr);	// redirect sfml errors to nothing, we want to handle errors on our own
	}

	AssetManager::~AssetManager()
	{
		for(auto & a : animTextures)
		{
			delete a.second;
		}

		for(auto & t : textures)
		{
			delete t.second;
		}

		for(auto & s : soundBuffers)
		{
			delete s.second;
		}

		for(auto & m : music)
		{
			delete m.second;
		}

		for(auto & f : fonts)
		{
			delete f.second;
		}

		for(auto & s : scripts)
		{
			delete s.second;
		}
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

		for(auto & f : mod.getFiles())
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
		for(auto & a : animTextures)
		{
			delete a.second;
		}

		for(auto & b : batches)
		{
			delete b.second;
		}

		for(auto & t : textures)
		{
			delete t.second;
		}

		for(auto & s : soundBuffers)
		{
			delete s.second;
		}

		for(auto & m : music)
		{
			delete m.second;
		}

		for(auto & f : fonts)
		{
			delete f.second;
		}

		for(auto & s : scripts)
		{
			delete s.second;
		}

		animTextures.clear();
		batches.clear();
		textures.clear();
		soundBuffers.clear();
		music.clear();
		fonts.clear();
		scripts.clear();
	}

	void AssetManager::setSmooth(bool s)
	{
		smooth = s;

		for(auto & t : textures)
		{
			t.second->setSmooth(smooth);
		}
	}

	bool AssetManager::newSpriteBatch(const std::string& t, unsigned int s)
	{
		if(batches.find(t) == batches.end())
		{
			sf::Texture* texture = getTexture(t);

			if(texture)
			{
				batches[t] = new SpriteBatch(*texture, s);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	AnimTexture* AssetManager::getAnimTexture(const std::string& n)
	{
		if(animTextures.find(n) != animTextures.end())
		{
			return animTextures.find(n)->second;
		}
		else
		{
			log << "[WARNING]: No \"" << n << "\" anim file exists\n";
		}

		return nullptr;
	}

	SpriteBatch* AssetManager::getBatch(const std::string& n)
	{
		if(batches.find(n) != batches.end())
		{
			return batches.find(n)->second;
		}
		else
		{
			log << "[WARNING]: No\"" << n << "\" batch exists\n";
		}

		return nullptr;
	}

	sf::Texture* AssetManager::getTexture(const std::string& n)
	{
		if(textures.find(n) != textures.end())
		{
			return textures.find(n)->second;
		}
		else
		{
			log << "[WARNING]: No \"" << n << "\" texture file exists\n";
		}

		return nullptr;
	}

	sf::SoundBuffer* AssetManager::getSoundBuffer(const std::string& n)
	{
		if(soundBuffers.find(n) != soundBuffers.end())
		{
			return soundBuffers.find(n)->second;
		}
		else
		{
			log << "[WARNING]: No \"" << n << "\" sound buffer file exists\n";
		}

		return nullptr;
	}

	sf::Music* AssetManager::getSong(const std::string& n)
	{
		if(music.find(n) != music.end())
		{
			return music.find(n)->second;
		}
		else
		{
			log << "[WARNING]: No \"" << n << "\" music file exists\n";
		}

		return nullptr;
	}

	sf::Font* AssetManager::getFont(const std::string& n)
	{
		if(fonts.find(n) != fonts.end())
		{
			return fonts.find(n)->second;
		}
		else
		{
			log << "[WARNING]: No \"" << n << "\" font file exists\n";
		}

		return nullptr;
	}

	Script* AssetManager::getScript(const std::string& n)
	{
		if(scripts.find(n) != scripts.end())
		{
			return scripts.find(n)->second;
		}
		else
		{
			log << "[WARNING]: No \"" << n << "\" script file exists\n";
		}

		return nullptr;
	}

	bool AssetManager::loadAnimTexture(const std::string& file)
	{
		std::string fileName = file.substr(file.find_last_of('/') + 1);

		animTextures.emplace(fileName, new AnimTexture());

		if(!animTextures[fileName]->loadFromFile(file))
		{
			log << "[WARNING]: Unable to load " << file << " as an anim\n";

			delete animTextures[fileName];

			animTextures.erase(fileName);
			return false;
		}

		log << "Anim:\t" << fileName << '\n';

		return true;
	}

	bool AssetManager::loadTexture(const std::string& file)
	{
		std::string fileName = file.substr(file.find_last_of('/') + 1);

		textures.emplace(fileName, new sf::Texture());

		if(!textures[fileName]->loadFromFile(file))
		{
			log << "[WARNING]: Unable to load " << file << " as a texture.\n";

			delete textures[fileName];

			textures.erase(fileName);
			return false;
		}

		textures[fileName]->setSmooth(smooth);

		log << "Texture:\t" << fileName << '\n';

		return true;
	}

	bool AssetManager::loadSound(const std::string& file)
	{
		std::string fileName = file.substr(file.find_last_of('/') + 1);

		soundBuffers.emplace(fileName, new sf::SoundBuffer());

		if(!soundBuffers[fileName]->loadFromFile(file))
		{
			log << "[WARNING]: Unable to load " << file << " as a sound.\n";

			// delete new'd soundbuffer
			delete soundBuffers[fileName];

			soundBuffers.erase(fileName);
			return false;
		}

		log << "Sound:\t" << fileName << '\n';

		return true;
	}

	bool AssetManager::loadSong(const std::string& file)
	{
		std::string fileName = file.substr(file.find_last_of('/') + 1);

		music.emplace(fileName, new sf::Music());

		if(!music[fileName]->openFromFile(file))
		{
			log << "[WARNING]: Unable to open " << file << " as a music file.\n";

			// delete new'd music
			delete music[fileName];

			music.erase(fileName);
			return false;
		}

		log << "Music:\t" << fileName << '\n';

		return true;
	}

	bool AssetManager::loadFont(const std::string& file)
	{
		std::string fileName = file.substr(file.find_last_of('/') + 1);

		fonts.emplace(fileName, new sf::Font());

		if(!fonts[fileName]->loadFromFile(file))
		{
			log << "[WARNING]: Unable to load " << file << " as a font.\n";

			// delete new'd font
			delete fonts[fileName];

			fonts.erase(fileName);
			return false;
		}

		log << "Font:\t" << fileName << '\n';

		return true;
	}

	bool AssetManager::loadScript(const std::string&)
	{
		return false;
	}

	bool AssetManager::loadResource(const std::string& file)
	{
		// this if chain checks what folder the file is in
		if(file.find("/anims/") != std::string::npos)
		{
			return loadAnimTexture(file);
		}
		else if(file.find("/textures/") != std::string::npos)
		{
			return loadTexture(file);
		}
		else if(file.find("/sounds/") != std::string::npos)
		{
			return loadSound(file);
		}
		else if(file.find("/music/") != std::string::npos)
		{
			return loadSong(file);
		}
		else if(file.find("/fonts/") != std::string::npos)
		{
			return loadFont(file);
		}
		else if(file.find("/scripts/") != std::string::npos)
		{
			return loadScript(file);
		}
		else if(file.find(".txt") != std::string::npos)
		{
			// ignore *.txt files, but don't throw a warning/error
			log << "Ignoring " << file << '\n';
		}
		else
		{
			log << "[WARNING]: " << file << " is an unknown resource type.\n";
			return false;
		}

		return true;
	}
}
