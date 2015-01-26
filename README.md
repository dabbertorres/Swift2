# Swift2
Game framework powered by SFML, OpenGL, Lua, and tinyxml2

# To Use
Create a new class, and publically inherit from swift::Game.

You'll need to call swift::Game's constructor with 2 arguments, the first, the title of your game.
The second, the engine ticks per second you want your game to run at. This is essentially the "updates per second".

Then, you'll have to implement a few functions:
```c++
void start(int c, char** argv);
void loadAssets();
void loadMods();
void initState();
void initScripting();
```

Here's a few examples of these functions:
```c++
class MyGame: public swift::Game
{
	MyGame() : Game("My Game", 30)
	{}

	void start(int c, char** args)
	{
		// give the path to your settings file here.
		// virtual function, in case you want to handle or add settings
		loadSettings("./data/settings.ini");

		// does what it says it does.
		// virtual as well
		handleLaunchOps(c, args);

		// give the path to your dictionary of choice.
		// If you're only supporting one language, go ahead and give a direct path
		// otherwise, the 'language' string will be set via the loadSettings function
		dictionary.loadFile("./data/dictionaries" + language + ".dic");

		// loads your asset folders.
		// pure virtual
		loadAssets();

		// loads mods in your mod folder
		// pure virtual
		loadMods();

		// grab your favorite font that was loaded earlier in loadAssets()
		defaultFont = *assets.getFont("./data/fonts/segoeuisl.ttf");

		// pretty simple, sets up the window, based off of settings.
		setupWindow();

		// starts up the state system
		initState();

		// starts up the scripting system
		initScripting();
	}

	void TheGame::loadAssets()
	{
		assets.setSmooth(smoothing);
		assets.loadResourceFolder("./data/anims");
		assets.loadResourceFolder("./data/textures");
		assets.loadResourceFolder("./data/fonts");
		assets.loadResourceFolder("./data/music");
		assets.loadResourceFolder("./data/scripts");
		assets.loadResourceFolder("./data/sounds");
		
		// make log file a little prettier
		swift::log << '\n';
	}
	
	void TheGame::loadMods()
	{
		// find all mods
		mods.loadMods("./data/mods");

		// this would be where you normally conditionally load up mods
		for(auto& m : mods.getMods())
		{
			assets.loadMod(m.second.mod);
		}
	}
	
	void TheGame::initState()
	{
		// state setup
		states.push(new GameMenu(window, assets, soundPlayer, musicPlayer, settings, dictionary, states));
	}
	
	void TheGame::initScripting()
	{
		GameScript::setAssetManager(assets);
		GameScript::setClock(GameTime);
		GameScript::setWindow(window);
		GameScript::setSettings(settings);
		GameScript::setKeyboard(keyboard);
	}	
};
```

Not too bad, eh? Well, at least I don't think so. Of course, you can just modify everything anyways if you need something special.

Afterwards, get a main function going that looks something like this:
```c++
#include "MyGame.hpp"

int main(int argc, char** argv)
{
	MyGame game;

	game.start();

	game.gameLoop();

	return 0;
}
```

Compile, link, run, and it should work! Mostly, that is. Won't do too much though. 

From there, to add actual functionality and State to your game, you'll need to inherit from swift::State, to create different States for your game to be in, if you want Lua Scripting support, inherit from swift::AssetManager and swift::Script, and to make a "World" for your game to happen in, inherit from swift::World. I'll add more examples for those soon!

Then, at that point, it's (almost) time to create content and code your game! Woo!
