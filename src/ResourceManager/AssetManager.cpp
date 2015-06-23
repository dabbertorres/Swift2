#include "AssetManager.hpp"

#include <SFML/System/Err.hpp>

namespace swift
{
	AssetManager::AssetManager()
	:	smooth(false)
	{
		sf::err().rdbuf(nullptr);	// redirect sfml errors to nothing, we want to handle errors on our own
	}

	AssetManager::~AssetManager()
	{
		clean();
	}

	bool AssetManager::loadResourceFolder(const gfs::Path& folder)
	{
		if(!folder)
		{
			Logger::get() << "[ERROR]: Could not read folder: \"" << folder << "\"\n";
			return false;
		}

		gfs::PathContents resources = gfs::contents(folder);
		
		for(auto& p : resources)
		{
			if(p.type() == gfs::Path::Type::Directory)
			{
				loadResourceFolder(p);
			}
			else if(p.type() == gfs::Path::Type::File)
			{
				loadResource(p);
			}
		}

		return true;
	}
	
	bool AssetManager::loadMods(const gfs::Path& modsFolder)
	{
		if(!modsFolder)
		{
			Logger::get() << "[ERROR]: Could not read mods folder: \"" << modsFolder << "\"\n";
			return false;
		}
		
		// get mods to load from mod file
		// each save should have a mods.ini which says which mods are enabled on that save
		// those mods should be loaded when that save is loaded,
		// and unloaded when that save is unloaded
//		gfs::Path modsIni = modsFolder / "mods.ini";
//		
//		if(modsIni)
//		{
//			Settings mods;
//		}
		
		gfs::PathContents modFolders = gfs::contents(modsFolder);
		
		for(auto& m : modFolders)
		{
			if(m.type() == gfs::Path::Type::Directory)
			{
				std::string name;
				std::string version;
				std::string author;
				std::string description;
				
				Settings info;
				info.loadFromFile(m + "info.txt");
				
				bool nameError = info.get("name", name);
				bool versionError = info.get("version", version);
				bool authorError = info.get("author", author);
				bool descriptionError = info.get("description", description);
				
				if(!nameError || !versionError || !authorError || !descriptionError)
				{
					Logger::get() << "[WARNING]: Ill formed info.txt for mod \"" << m.name() << "\", not loading.\n";
					continue;
				}
				
				mods.emplace(name, Mod{m, name, version, author, description});
				
				Logger::get() << "\nLoading mod: " << name << '\n';
				Logger::get() << "\tVersion: " << version << '\n';
				Logger::get() << "\tBy: " << author << '\n';
				Logger::get() << '\t' << description << '\n';
				
				loadResourceFolder(m);
			}
		}

		return true;
	}
	
	void AssetManager::clean()
	{
		anims.clear();
		batches.clear();
		textures.clear();
		sounds.clear();
		music.clear();
		fonts.clear();
		scripts.clear();
	}
	
	void AssetManager::setSmooth(bool s)
	{
		smooth = s;

		for(auto& t : textures)
		{
			t.second->setSmooth(smooth);
		}
	}
	
	bool AssetManager::newSpriteBatch(const std::string& t)
	{
		if(batches.find(t) == batches.end())
		{
			sf::Texture* texture = getTexture(t);

			if(texture)
			{
				batches[t] = std::make_unique<SpriteBatch>(*texture);
				return true;
			}
		}
		
		return false;
	}

	AnimTexture* AssetManager::getAnim(const std::string& n)
	{
		if(anims.find(n) != anims.end())
		{
			return anims.find(n)->second.get();
		}
		
		Logger::get() << "[WARNING]: No \"" << n << "\" anim file exists\n";

		return nullptr;
	}
	
	Dictionary* AssetManager::getDict(const std::string& n)
	{
		if(dicts.find(n) != dicts.end())
		{
			return dicts.find(n)->second.get();
		}
		
		Logger::get() << "[WARNING]: No \"" << n << "\" dic file exists\n";

		return nullptr;
	}

	sf::Font* AssetManager::getFont(const std::string& n)
	{
		if(fonts.find(n) != fonts.end())
		{
			return fonts.find(n)->second.get();
		}
		
		Logger::get() << "[WARNING]: No \"" << n << "\" font file exists\n";

		return nullptr;
	}

	sf::Music* AssetManager::getMusic(const std::string& n)
	{
		if(music.find(n) != music.end())
		{
			return music.find(n)->second.get();
		}
		
		Logger::get() << "[WARNING]: No \"" << n << "\" music file exists\n";

		return nullptr;
	}

	Script* AssetManager::getScript(const std::string& n)
	{
		if(scripts.find(n) != scripts.end())
		{
			return scripts.find(n)->second.get();
		}
		
		Logger::get() << "[WARNING]: No \"" << n << "\" script file exists\n";
		
		return nullptr;
	}

	sf::SoundBuffer* AssetManager::getSound(const std::string& n)
	{
		if(sounds.find(n) != sounds.end())
		{
			return sounds.find(n)->second.get();
		}
		
		Logger::get() << "[WARNING]: No \"" << n << "\" sound buffer file exists\n";
		
		return nullptr;
	}

	SpriteBatch* AssetManager::getBatch(const std::string& n)
	{
		if(batches.find(n) != batches.end())
		{
			return batches.find(n)->second.get();
		}
		
		Logger::get() << "[WARNING]: No\"" << n << "\" batch exists\n";

		return nullptr;
	}

	sf::Texture* AssetManager::getTexture(const std::string& n)
	{
		if(textures.find(n) != textures.end())
		{
			return textures.find(n)->second.get();
		}
		
		Logger::get() << "[WARNING]: No \"" << n << "\" texture file exists\n";
		
		return nullptr;
	}

	bool AssetManager::loadAnim(const gfs::Path& file)
	{
		std::string filename = file.filename();

		anims.emplace(filename, std::make_unique<AnimTexture>());

		if(!anims[filename]->loadFromFile(file))
		{
			Logger::get() << "[WARNING]: Unable to load " << file << " as an anim\n";

			anims.erase(filename);
			return false;
		}

		Logger::get() << "Anim:\t" << filename << '\n';

		return true;
	}
	
	bool AssetManager::loadDict(const gfs::Path& file)
	{
		std::string filename = file.name();

		dicts.emplace(filename, std::make_unique<Dictionary>());

		if(!dicts[filename]->loadFromFile(file))
		{
			Logger::get() << "[WARNING]: Unable to load " << file << " as a dictionary\n";

			dicts.erase(filename);
			return false;
		}

		Logger::get() << "Dictionary:\t" << filename << '\n';

		return true;
	}

	bool AssetManager::loadFont(const gfs::Path& file)
	{
		std::string filename = file.filename();

		fonts.emplace(filename, std::make_unique<sf::Font>());

		if(!fonts[filename]->loadFromFile(file))
		{
			Logger::get() << "[WARNING]: Unable to load " << file << " as a font.\n";

			fonts.erase(filename);
			return false;
		}

		Logger::get() << "Font:\t" << filename << '\n';

		return true;
	}

	bool AssetManager::loadMusic(const gfs::Path& file)
	{
		std::string filename = file.filename();

		music.emplace(filename, std::make_unique<sf::Music>());

		if(!music[filename]->openFromFile(file))
		{
			Logger::get() << "[WARNING]: Unable to open " << file << " as a music file.\n";

			music.erase(filename);
			return false;
		}

		Logger::get() << "Music:\t" << filename << '\n';

		return true;
	}
	
	bool AssetManager::loadScript(const gfs::Path&)
	{
		return false;
	}
	
	bool AssetManager::loadSound(const gfs::Path& file)
	{
		std::string filename = file.filename();

		sounds.emplace(filename, std::make_unique<sf::SoundBuffer>());

		if(!sounds[filename]->loadFromFile(file))
		{
			Logger::get() << "[WARNING]: Unable to load " << file << " as a sound.\n";

			sounds.erase(filename);
			return false;
		}

		Logger::get() << "Sound:\t" << filename << '\n';

		return true;
	}
	
	bool AssetManager::loadTexture(const gfs::Path& file)
	{
		std::string filename = file.filename();

		textures.emplace(filename, std::make_unique<sf::Texture>());

		if(!textures[filename]->loadFromFile(file))
		{
			Logger::get() << "[WARNING]: Unable to load " << file << " as a texture.\n";

			textures.erase(filename);
			return false;
		}

		textures[filename]->setSmooth(smooth);

		Logger::get() << "Texture:\t" << filename << '\n';

		return true;
	}

	bool AssetManager::loadResource(const gfs::Path& file)
	{
		if(!file)
		{
			return false;
		}
		
		// this if chain checks what folder the file is in
		if(file.parent().name().find("anims") != std::string::npos)
		{
			return loadAnim(file);
		}
		else if(file.parent().name().find("dicts") != std::string::npos)
		{
			return loadDict(file);
		}
		else if(file.parent().name().find("fonts") != std::string::npos)
		{
			return loadFont(file);
		}
		else if(file.parent().name().find("music") != std::string::npos)
		{
			return loadMusic(file);
		}
		else if(file.parent().name().find("scripts") != std::string::npos)
		{
			return loadScript(file);
		}
		else if(file.parent().name().find("sounds") != std::string::npos)
		{
			return loadSound(file);
		}
		else if(file.parent().name().find("textures") != std::string::npos)
		{
			return loadTexture(file);
		}
		else
		{
			Logger::get() << "[INFO]: " << file << " is an unknown resource type.\n";
			return false;
		}
	}
}
