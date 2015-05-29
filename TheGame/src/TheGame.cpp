#include "TheGame.hpp"

#include "GameMenu.hpp"
#include "GameSettings.hpp"
#include "GameScript.hpp"

namespace tg
{
	TheGame::TheGame(int c, char** args)
	:	Game("TheGame", 60),
		assets(getResourcePath()),
		soundLevel(100),
		musicLevel(75),
		language("en")
	{
		// loads settings from the settings file
		loadSettings(getResourcePath() / "settings.ini");
		
		// loads a dictionary
		dictionary.loadFile(getResourcePath() / "dictionaries/" + language + ".dic");
		
		loadAssets();
		
		// gotta set this if you want any text to display
		defaultFont = *assets.getFont("segoeuisl.ttf");
		
		//window.setIcon(SwiftEngineIcon.width, SwiftEngineIcon.height, SwiftEngineIcon.pixel_data);	// need to figure out icon stuff
		
		initState();
		
		initScripting();
	}
	
	void TheGame::gameHandleEvents(const sf::Event& event)
	{
		states.read()->handleEvent(event);
	}
	
	void TheGame::gameUpdate(const sf::Time& dt)
	{
		states.read()->update(dt);
	}
	
	void TheGame::manageStates()
	{
		if(states.read()->switchFrom())
		{
			states.pop();

			if(states.empty())
			{
				running = false;
			}
		}
	}
	
	void TheGame::gameDraw()
	{
		states.read()->draw();
	}
	
	bool TheGame::loadSettings(const gfs::Path& file)
	{
		// settings file settings
		if(!file || !gameSettings.loadFile(file))
		{
			swift::log << "Could not open settings file, default settings will be used\n";
			return false;
		}

		gameSettings.get("fullscreen", fullscreen);
		gameSettings.get("vsync", verticalSync);
		gameSettings.get("res.x", resolution.x);
		gameSettings.get("res.y", resolution.y);
		gameSettings.get("sound", soundLevel);
		gameSettings.get("music", musicLevel);
		gameSettings.get("lang", language);
		
		return true;
	}
	
	void TheGame::loadAssets()
	{
		assets.loadResourceFolder(getResourcePath());
		assets.loadMods(getResourcePath() / "../mods");

		// make log file a little prettier
		swift::log << '\n';
	}
	
	void TheGame::initState()
	{
		states.push(new GameMenu(window, assets, soundPlayer, musicPlayer, gameSettings, dictionary, states));
	}
	
	void TheGame::initScripting()
	{
		GameScript::setResourcePath(getResourcePath());
		GameScript::setAssetManager(assets);
		GameScript::setClock(gameTime);
		GameScript::setWindow(window);
		GameScript::setSettings(gameSettings);
	}
}
