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
		soundLevel(100),
		musicLevel(75)
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
		
		// get settings to initialize engine
		loadSettings(getResourcePath() / "settings.ini");
		
		// arguments override settings
		handleArgs(argc, argv);
		
		// get stuff so we can do stuff
		loadAssets();
		
		// gotta set this if you want any text to display
		defaultFont = assets.getFont("segoeuisl.ttf");
		
		//window.setIcon(SwiftEngineIcon.width, SwiftEngineIcon.height, SwiftEngineIcon.pixel_data);	// need to figure out icon stuff
		
		// can't do anything without state (well, in this case)
		initState();
		
		// scripting if you want it
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
		if(states.read()->isDone())
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
		if(!file || !gameSettings.loadFromFile(file))
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
		
		soundPlayer.setVolume(soundLevel / 100.f);
		musicPlayer.setVolume(musicLevel / 100.f);
		
		return true;
	}
	
	void TheGame::loadAssets()
	{
		assets.loadResourceFolder(getResourcePath() / "anims");
		assets.loadResourceFolder(getResourcePath() / "dicts");
		assets.loadResourceFolder(getResourcePath() / "fonts");
		assets.loadResourceFolder(getResourcePath() / "maps");
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
		states.push(new GameMenu(window, assets, soundPlayer, musicPlayer, gameSettings, states), false);
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
