# Swift2
Game framework powered by SFML, OpenGL, Lua, and tinyxml2

# To Use
Create a new class, and publically inherit from swift::Game.

You'll need to call swift::Game's constructor with 2 arguments, the first, the title of your game.
The second, the engine ticks per second you want your game to run at. This is essentially the "updates per second".

Then, implement "void start(int c, char** args)" function.
You'll need to a bunch of functions in it to get started.
Here's an example:

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

		// pretty simple, sets up the window, based off of settings.
		setupWindow();

		// loads your asset folders.
		// virtual
		loadAssets();

		// loads mods in your mod folder
		// virtual, for changing behavior. By default, it loads everything in the mod folder
		loadMods();

		// grab your favorite font that was loaded earlier in loadAssets()
		defaultFont = assets.getFont("./data/fonts/segoeuisl.ttf");

		// starts up the state system
		initState();

		// starts up the scripting system
		initScripting();
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

	game.finish();

	return 0;
}
```

Compile, link, run, and it should work! Mostly, that is. Won't do too much though. Maybe even crash.
I've got a bit more work (at the time this was written, 1/17/15) to do on opening the engine up, mostly with the different States, but
that should come along soon enough. Right now, it will try to load textures, maps, scripts, and stuff that you don't have.
Once I clean that up, you'll have a few more classes to inherit from (or create, haven't decided) and register with the engine.

Then, at that point, it's (hopefully) time to create content and code your game! Woo!
