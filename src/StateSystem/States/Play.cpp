#include "Play.hpp"

#include <fstream>

#include "../../ResourceManager/AssetManager.hpp"

/* SoundSystem headers */
#include "../../SoundSystem/SoundPlayer.hpp"
#include "../../SoundSystem/MusicPlayer.hpp"

/* EntitySystem headers */
#include "../../EntitySystem/Components/Animated.hpp"
#include "../../EntitySystem/Components/Pathfinder.hpp"

/* Pathfinding headers */
#include "../../Pathfinding/Path.hpp"

namespace swift
{
	Play::Play(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic)
	:	State(win, am, sp, mp, set, dic),
	    activeState(nullptr),
		activeWorld(nullptr),
		player(nullptr),
		playView({0, 0, static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y)}),
		currentZoom(1.f)
	{
		returnType = State::Type::Play;
	}

	Play::~Play()
	{
		std::ofstream fout;
		
		fout.open("./data/saves/currentWorld");
		fout << activeWorld->getName() << '\n';
		fout << activeWorld->tilemap.getFile() << '\n';
		fout.close();
		
		for(auto& w : worlds)
			delete w.second;

		for(auto& s : scripts)
			removeScript(s.first);
	}

	bool Play::switchFrom()
	{
		return returnType != State::Type::Play;
	}

	State::Type Play::finish()
	{
		return returnType;
	}

	Entity* Play::getPlayer() const
	{
		return player;
	}

	bool Play::addScript(const std::string& scriptFile)
	{
		if(scripts.find(scriptFile) == scripts.end())
		{
			scripts.emplace(scriptFile, assets.getScript(scriptFile));
			scripts[scriptFile]->start();
			return true;
		}
		else
			return false;
	}

	bool Play::removeScript(const std::string& scriptFile)
	{
		if(scripts.find(scriptFile) != scripts.end())
		{
			if(!scripts[scriptFile]->save("./data/saves/" + scriptFile.substr(scriptFile.find_last_of('/') + 1) + ".script"))
				log << "[WARNING]: Could not save script: " << scriptFile << "!\n";
			scripts[scriptFile]->reset();
			scripts.erase(scriptFile);
			return true;
		}
		else
			return false;
	}

	void Play::changeWorld(const std::string& name, const std::string& mapFile)
	{
		worlds.emplace(name, new World(name, assets, soundPlayer, musicPlayer, {}));
		World* newWorld = worlds[name];

		// setup world
		bool mapResult = newWorld->tilemap.loadFile(mapFile);
		bool textureResult = newWorld->tilemap.loadTexture(*assets.getTexture(newWorld->tilemap.getTextureFile()));

		if(!mapResult)
			log << "[ERROR]: Loading tilemap \"" << mapFile << "\" failed.\n";

		if(!textureResult)
			log << "[ERROR]: Setting texture for \"" << mapFile << "\" failed.\n";

		if(!mapResult || !textureResult)
		{
			worlds.erase(name);	// undo what we did and exit since loading the world failed
			return;
		}

		// get the player
		if(activeWorld)
		{
			// copy over play from current world to new world
			Entity* newPlayer = newWorld->addEntity();
			*newPlayer = *player;
			player = newPlayer;

			activeWorld->removeEntity(0);	// delete player from current world

			// delete old world
			std::string oldWorld = activeWorld->getName();
			delete activeWorld;
			worlds.erase(oldWorld);

			// load the world's save file
			bool loadResult = newWorld->load();
			
			if(!loadResult)
				log << "[WARNING]: Loading World data for world: \"" << name << "\" failed.\n";
		}
		else
		{
			// load the world's save file
			bool loadResult = newWorld->load();
			
			if(!loadResult)
				log << "[WARNING]: Loading World data for world: \"" << name << "\" failed.\n";
			
			for(auto& e : newWorld->getEntities())
			{
				if(e->has<Controllable>())
				{
					player = e;
					break;
				}
			}
		}

		activeWorld = newWorld;
		Script::setWorld(*activeWorld);
	}
	
	void Play::loadLastWorld()
	{
		std::ifstream fin;
		
		std::string worldName;
		std::string tilemapFile;
		
		fin.open("./data/saves/currentWorld");
		std::getline(fin, worldName);
		std::getline(fin, tilemapFile);
		fin.close();

		// create worlds
		changeWorld(worldName, tilemapFile);
		
		Script::setWorld(*activeWorld);
	}
	
	void Play::updateScripts()
	{
		std::vector<std::string> doneScripts;

		for(auto& s : scripts)
		{
			s.second->update();

			// check if script is done, if so, push it for deletion
			if(s.second->toDelete())
				doneScripts.push_back(s.first);
		}

		// remove all done scripts
		for(auto& s : doneScripts)
		{
			removeScript(s);
		}
	}
}
