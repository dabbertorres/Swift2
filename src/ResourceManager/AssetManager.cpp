#include "AssetManager.hpp"

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
			log << "[ERROR]: Could not read folder: \"" << folder << "\"\n";
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
			log << "[ERROR]: Could not read mods folder: \"" << modsFolder << "\"\n";
			return false;
		}
		
		// get mods to load from mod file
		gfs::Path modsIni = modsFolder / "mods.ini";
		
		if(modsIni)
		{
			Settings mods;
		}
		
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
				info.loadFile(m + "info.txt");
				
				bool nameError = info.get("name", name);
				bool versionError = info.get("version", version);
				bool authorError = info.get("author", author);
				bool descriptionError = info.get("description", description);
				
				if(!nameError || !versionError || !authorError || !descriptionError)
				{
					log << "[WARNING]: Ill formed info.txt for mod \"" << m.name() << "\", not loading.\n";
					continue;
				}
				
				mods.emplace(name, Mod{m, name, version, author, description});
				
				log << "\nLoading mod: " << name << '\n';
				log << "\tVersion: " << version << '\n';
				log << "\tBy: " << author << '\n';
				log << '\t' << description << '\n';
				
				loadResourceFolder(m);
			}
		}

		return true;
	}

	void AssetManager::clean()
	{
		for(auto& a : animTextures)
		{
			delete a.second;
		}

		for(auto& b : batches)
		{
			delete b.second;
		}

		for(auto& t : textures)
		{
			delete t.second;
		}

		for(auto& s : soundBuffers)
		{
			delete s.second;
		}

		for(auto& m : music)
		{
			delete m.second;
		}

		for(auto& f : fonts)
		{
			delete f.second;
		}

		for(auto& s : scripts)
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

	bool AssetManager::newSpriteBatch(const std::string& t)
	{
		if(batches.find(t) == batches.end())
		{
			sf::Texture* texture = getTexture(t);

			if(texture)
			{
				batches[t] = new SpriteBatch(*texture);
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

	bool AssetManager::loadAnimTexture(const gfs::Path& file)
	{
		std::string filename = file.filename();

		animTextures.emplace(filename, new AnimTexture());

		if(!animTextures[filename]->loadFromFile(file))
		{
			log << "[WARNING]: Unable to load " << file << " as an anim\n";

			delete animTextures[filename];

			animTextures.erase(filename);
			return false;
		}

		log << "Anim:\t" << filename << '\n';

		return true;
	}

	bool AssetManager::loadTexture(const gfs::Path& file)
	{
		std::string filename = file.filename();

		textures.emplace(filename, new sf::Texture());

		if(!textures[filename]->loadFromFile(file))
		{
			log << "[WARNING]: Unable to load " << file << " as a texture.\n";

			delete textures[filename];

			textures.erase(filename);
			return false;
		}

		textures[filename]->setSmooth(smooth);

		log << "Texture:\t" << filename << '\n';

		return true;
	}

	bool AssetManager::loadSound(const gfs::Path& file)
	{
		std::string filename = file.filename();

		soundBuffers.emplace(filename, new sf::SoundBuffer());

		if(!soundBuffers[filename]->loadFromFile(file))
		{
			log << "[WARNING]: Unable to load " << file << " as a sound.\n";

			// delete new'd soundbuffer
			delete soundBuffers[filename];

			soundBuffers.erase(filename);
			return false;
		}

		log << "Sound:\t" << filename << '\n';

		return true;
	}

	bool AssetManager::loadSong(const gfs::Path& file)
	{
		std::string filename = file.filename();

		music.emplace(filename, new sf::Music());

		if(!music[filename]->openFromFile(file))
		{
			log << "[WARNING]: Unable to open " << file << " as a music file.\n";

			// delete new'd music
			delete music[filename];

			music.erase(filename);
			return false;
		}

		log << "Music:\t" << filename << '\n';

		return true;
	}

	bool AssetManager::loadFont(const gfs::Path& file)
	{
		std::string filename = file.filename();

		fonts.emplace(filename, new sf::Font());

		if(!fonts[filename]->loadFromFile(file))
		{
			log << "[WARNING]: Unable to load " << file << " as a font.\n";

			// delete new'd font
			delete fonts[filename];

			fonts.erase(filename);
			return false;
		}

		log << "Font:\t" << filename << '\n';

		return true;
	}

	bool AssetManager::loadScript(const gfs::Path&)
	{
		return false;
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
			return loadAnimTexture(file);
		}
		else if(file.parent().name().find("textures") != std::string::npos)
		{
			return loadTexture(file);
		}
		else if(file.parent().name().find("sounds") != std::string::npos)
		{
			return loadSound(file);
		}
		else if(file.parent().name().find("music") != std::string::npos)
		{
			return loadSong(file);
		}
		else if(file.parent().name().find("fonts") != std::string::npos)
		{
			return loadFont(file);
		}
		else if(file.parent().name().find("scripts") != std::string::npos)
		{
			return loadScript(file);
		}
		else
		{
			log << "[INFO]: " << file << " is an unknown resource type.\n";
			return false;
		}

		return true;
	}
}
