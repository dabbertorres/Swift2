#include "TheGame.hpp"

#include "GameMenu.hpp"
#include "GameSettingsMenu.hpp"
#include "GameScript.hpp"

#include "SystemInfo/SystemInfo.hpp"

#include "Logger/Logger.hpp"

namespace tg
{
	TheGame::TheGame(int argc, char** argv)
	:	Game("TheGame", 60),
		assets(getResourcePath()),
		soundLevel(100),
		musicLevel(75),
		language("en")
	{
		// init Logger first
		swift::Logger::setFile(getResourcePath() / "TheGame.log");
		
		// get System Info
		swift::Logger::get()	<< "OS:\t\t" << swift::getOSName() << '\n'
								<< "Version:\t" << swift::getOSVersion() << '\n'
								<< "Arch:\t\t" << swift::getOSArch() << '\n'
								<< "Total Mem:\t" << swift::getTotalMem() << '\n'
								<< "CPU:\t\t" << swift::getCPUModel() << '\n'
								<< "Video Vendor:\t" << swift::getVideoVendor() << '\n'
								<< "Video Card:\t" << swift::getVideoCard() << '\n'
								<< "Video Driver:\t" << swift::getVideoDriver() << "\n\n";
		
		// loads settings from the settings file
		loadSettings(getResourcePath() / "settings.ini");
		
		handleArgs(argc, argv);
		
		// loads a dictionary
		dictionary.loadFile(getResourcePath() / ("dict/" + language + ".dic"));
		
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
			swift::Logger::get() << "Could not open settings file, default settings will be used\n";
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
		assets.loadResourceFolder(getResourcePath() / "anims");
		assets.loadResourceFolder(getResourcePath() / "dict");
		assets.loadResourceFolder(getResourcePath() / "fonts");
		//assets.loadResourceFolder(getResourcePath() / "maps");
		assets.loadResourceFolder(getResourcePath() / "music");
		assets.loadResourceFolder(getResourcePath() / "scripts");
		assets.loadResourceFolder(getResourcePath() / "sounds");
		assets.loadResourceFolder(getResourcePath() / "textures");
		assets.loadMods(getResourcePath() / "../mods");

		// make log file a little prettier
		swift::Logger::get() << '\n';
	}
	
	void TheGame::handleArgs(int argc, char** argv)
	{
		std::vector<std::string> args(argv + 1, argv + argc);
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
