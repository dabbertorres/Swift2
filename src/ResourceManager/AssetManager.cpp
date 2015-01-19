#include "AssetManager.hpp"

namespace swift
{
	AssetManager::AssetManager()
	{
		smooth = false;
		sf::err().rdbuf(nullptr);	// redirect sfml errors to nothing, we want to handle errors on our own
	}

	AssetManager::~AssetManager()
	{
		for(auto& a : animTextures)
			delete a.second;
		
		for(auto& t : textures)
			delete t.second;
		
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
		for(auto& a : animTextures)
			delete a.second;
		
		for(auto& t : textures)
			delete t.second;
		
		for(auto& s : soundBuffers)
			delete s.second;
			
		for(auto& m : music)
			delete m.second;
		
		for(auto& f : fonts)
			delete f.second;
		
		for(auto& s : scripts)
			delete s.second;
		
		animTextures.clear();
		textures.clear();
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
	
	AnimTexture* AssetManager::getAnimTexture(const std::string& n)
	{
		if(animTextures.find(n) != animTextures.end())
			return animTextures.find(n)->second;
		else
			log << "No \"" << n << "\" anim file exists\n";
		
		return nullptr;
	}

	sf::Texture* AssetManager::getTexture(const std::string& n)
	{
		if(textures.find(n) != textures.end())
			return textures.find(n)->second;
		else
			log << "No \"" << n << "\" texture file exists\n";
		
		return nullptr;
	}
	
	sf::SoundBuffer* AssetManager::getSoundBuffer(const std::string& n)
	{
		if(soundBuffers.find(n) != soundBuffers.end())
			return soundBuffers.find(n)->second;
		else
			log << "No \"" << n << "\" sound buffer file exists\n";
		
		return nullptr;
	}
	
	sf::Music* AssetManager::getSong(const std::string& n)
	{
		if(music.find(n) != music.end())
			return music.find(n)->second;
		else
			log << "No \"" << n << "\" music file exists\n";
		
		return nullptr;
	}
	
	sf::Font* AssetManager::getFont(const std::string& n)
	{
		if(fonts.find(n) != fonts.end())
			return fonts.find(n)->second;
		else
			log << "No \"" << n << "\" font file exists\n";
		
		return nullptr;
	}
	
	Script* AssetManager::getScript(const std::string& n)
	{
		if(scripts.find(n) != scripts.end())
			return scripts.find(n)->second;
		else
			log << "No \"" << n << "\" script file exists\n";
		
		return nullptr;
	}

	bool AssetManager::loadResource(const std::string& file)
	{
		// this if chain checks what folder the file is in
		if(file.find("/anims/") != std::string::npos)
		{
			animTextures.emplace(file, new AnimTexture());
			
			if(!animTextures[file]->loadFromFile(file))
			{
				log << "Unable to load " << file << " as an anim\n";
				
				delete animTextures[file];
				
				animTextures.erase(file);
				return false;
			}
			
			log << "Anim:\t" << file << '\n';
		}
		else if(file.find("/textures/") != std::string::npos)
		{
			textures.emplace(file, new sf::Texture());

			if(!textures[file]->loadFromFile(file))
			{
				log << "Unable to load " << file << " as a texture.\n";
				
				delete textures[file];
				
				textures.erase(file);
				return false;
			}
			
			textures[file]->setSmooth(smooth);

			log << "Texture:\t" << file << '\n';
		}
		else if(file.find("/sounds/") != std::string::npos)
		{
			soundBuffers.emplace(file, new sf::SoundBuffer());

			if(!soundBuffers[file]->loadFromFile(file))
			{
				log << "Unable to load " << file << " as a sound.\n";
				
				// delete new'd soundbuffer
				auto it = soundBuffers.end();
				it--;
				delete it->second;
				
				soundBuffers.erase(file);
				return false;
			}

			log << "Sound:\t" << file << '\n';
		}
		else if(file.find("/music/") != std::string::npos)
		{
			music.emplace(file, new sf::Music());

			if(!music[file]->openFromFile(file))
			{
				log << "Unable to open " << file << " as a music file.\n";
				
				// delete new'd music
				auto it = music.end();
				it--;
				delete it->second;
				
				music.erase(file);
				return false;
			}

			log << "Music:\t" << file << '\n';
		}
		else if(file.find("/fonts/") != std::string::npos)
		{
			fonts.emplace(file, new sf::Font());

			if(!fonts[file]->loadFromFile(file))
			{
				log << "Unable to load " << file << " as a font.\n";
				
				// delete new'd font
				auto it = fonts.end();
				it--;
				delete it->second;
				
				fonts.erase(file);
				return false;
			}

			log << "Font:\t" << file << '\n';
		}
		else if(file.find("/scripts/") != std::string::npos)
		{
			scripts.emplace(file, new Script());
			
			if(!scripts[file]->loadFromFile(file))
			{
				log << "Unable to load " << file << " as a script.\n";
				
				// delete new'd script
				auto it = scripts.end();
				it--;
				delete it->second;
				
				scripts.erase(file);
				return false;
			}
			
			log << "Script:\t" << file << '\n';
			
			scripts[file]->load("./data/saves/" + file.substr(file.find_last_of('/') + 1) + ".script");
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
