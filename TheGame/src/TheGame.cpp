#include "TheGame.hpp"

#include "GameMenu.hpp"
#include "GameSettings.hpp"
#include "GameScript.hpp"

namespace tg
{
	TheGame::TheGame()
		:	Game("TheGame", 60),
		    assets(getResourcePath())
	{
	}

	TheGame::~TheGame()
	{
	}

	void TheGame::start(int c, char** args)
	{
		// c is the total arguments
		// args is the arguments

		// loads settings from the settings file
		loadSettings(getResourcePath() + "../data/settings.ini");

		handleLaunchOps(c, args);

		// loads a dictionary
		dictionary.loadFile(getResourcePath() + "../data/dictionaries/" + language + ".dic");

		loadAssets();

		loadMods();

		// gotta set this if you want any text to display
		defaultFont = *assets.getFont("segoeuisl.ttf");

		setupWindow();

		//window.setIcon(SwiftEngineIcon.width, SwiftEngineIcon.height, SwiftEngineIcon.pixel_data);	// need to figure out icon stuff

		initState();

		initScripting();
	}

	void TheGame::loadAssets()
	{
		assets.setSmooth(smoothing);
		assets.loadResourceFolder(getResourcePath() + "../data/anims");
		assets.loadResourceFolder(getResourcePath() + "../data/textures");
		assets.loadResourceFolder(getResourcePath() + "../data/fonts");
		assets.loadResourceFolder(getResourcePath() + "../data/music");
		assets.loadResourceFolder(getResourcePath() + "../data/scripts");
		assets.loadResourceFolder(getResourcePath() + "../data/sounds");

		// make log file a little prettier
		swift::log << '\n';
	}

	void TheGame::loadMods()
	{
		// find all mods
		mods.loadMods(getResourcePath() + "../data/mods");

		// this would be where you normally conditionally load up mods
		for(auto & m : mods.getMods())
		{
			assets.loadMod(m.second.mod);
		}
	}

	void TheGame::initState()
	{
		// state setup
		states.push(new GameMenu(window, assets, soundPlayer, musicPlayer, settings, dictionary, states, getResourcePath()));
	}

	void TheGame::initScripting()
	{
		GameScript::setAssetManager(assets);
		GameScript::setClock(GameTime);
		GameScript::setWindow(window);
		GameScript::setSettings(settings);
		GameScript::setKeyboard(keyboard);
	}
}
