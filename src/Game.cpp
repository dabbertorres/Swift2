#include "Game.hpp"
#include <cstring>

namespace swift
{
	const std::string errorLog = "./data/log.txt";

	Game::Game() :	logger("Alpha", errorLog),
					console(500, 200, defaultFont, "[swift2]:")
	{
		// currentState = new Loading();

		// Set a bunch of defaults, just in case loadSettings() fails.
		// And a few other engine specific settings

		graphics = Quality::Medium;
		antiAliasing = 0;
		verticalSync = true;
		fullScreen = false;
		resolution.x = 800;
		resolution.y = 600;
		running = false;

		// engine integral settings
		ticksPerSecond = 20;
		maxFrameSkip = 5;
		
		defaultFont.loadFromFile(defaultFontFile);
	}

	Game::~Game()
	{
		//currentState = nullptr;
		/*std::map<std::string, LuaScript*>::iterator iter;
		for(iter = luaScripts.begin(); iter != luaScripts.end(); ++iter)
		{
			delete iter->second;
		}*/
	}

	// Do any pre-game data loading
	// Such as setting up the scripting virtual machine
	// and setting game quality settings.
	// That's about it
	void Game::Start(int c, char** args)
	{
		//newLuaScript("./data/scripts/test.lua");
		
		// c is the total arguments
		// args is the arguments

		// loads settings from the settings file
		loadSettings("./data/settings/settings.dat");
		
		handleLaunchOps(c, args);
		
		// Window set up.
		if(fullScreen)
			window.create(sf::VideoMode(resolution.x, resolution.y, 32), "Swift Engine", sf::Style::Fullscreen, contextSettings);
		else
			window.create(sf::VideoMode(resolution.x, resolution.y, 32), "Swift Engine", sf::Style::Titlebar | sf::Style::Close, contextSettings);
		
		sf::ContextSettings cs = window.getSettings();
		logger << "OpenGL version: " + std::to_string(cs.majorVersion) + '.' + std::to_string(cs.minorVersion);
		
		//window.setIcon(SwiftEngineIcon.width, SwiftEngineIcon.height, SwiftEngineIcon.pixel_data);
		window.setVerticalSyncEnabled(verticalSync);
		window.setKeyRepeatEnabled(false);

		//assetManager.setAntiAliasing(antiAliasing);
		
		// add some default keybindings
		keyboard.newBinding("toggleTerminal", sf::Keyboard::BackSlash, [&]()
		{
			console.activate(!console.isActivated());
		});
		
		keyboard.newBinding("exit", sf::Keyboard::Escape, [&]()
		{
			running = false;
		});
		
		// add some console commands
		console.addCommand("hello", [](ArgVec args)
		{
			return "Hello to you too!";
		});

		running = true;

		// fps display
		if(debug)
		{
			FPS.setFont(defaultFont);
			FPS.setScale(0.7, 0.7);
			FPS.setPosition(window.getSize().x - 80, 0);
		}
	}

	void Game::GameLoop()
	{
		NextGameTime = GameTime.getElapsedTime();

		float TimeSkip = 1000 / ticksPerSecond;	// convert to millseconds from seconds

		float lastTime = 0;

		float interpolation;

		while(running)
		{
			int loopCount = 0;

			// Time to Update if the current time is past the projected time, and we haven't skipped drawing too much
			while(GameTime.getElapsedTime() > NextGameTime && loopCount < maxFrameSkip)
			{
				Update();

				NextGameTime += sf::milliseconds(TimeSkip);
				loopCount++;
			}

			interpolation = float(GameTime.getElapsedTime().asMilliseconds() + TimeSkip - NextGameTime.asMilliseconds()) / TimeSkip;

			Draw(interpolation);

			float currentTime = GameTime.getElapsedTime().asSeconds();

			if(debug)
				fps = 1 / (currentTime - lastTime);

			lastTime = currentTime;
		}
	}

	void Game::Update()
	{
		if(debug)
			FPS.setString(sf::String(std::to_string(fps).substr(0, 6)));
			
		sf::Event event;
		while(window.pollEvent(event))
		{
			keyboard(event);
			mouse(event);
			
			// avoid having the console type the key that toggles it
			if(event.type == sf::Event::TextEntered && event.text.unicode != '\\')
				console.update(event);
			
			if(event.type == sf::Event::Closed)
				running = false;
		}
	}

	void Game::Draw(float i)
	{
		// with interpolation, make sure to have something like this:
		// viewPosition = position + (speed * interpolation)
		// objects will thus be rendered a little off of where they actually are
		// but the speed is so fast, it should be fine.
		// if I want to get fancy, I can predict even more to avoid render collision
		//
		// for(unsigned i = 0; i < currentState->objects.size(); i++)
		// 		window.draw(currentState->objects.at(i)->sprite);
		//
		// for animation, an array (or vector) holding all animation frames is all that
		// is needed. Changing the frame to be drawn every game tick is that is needed.

		// testing

		/* clear display */
		window.clear();
		
		/* state drawing */
		window.draw(console);
		
		/* other drawing */
		if(debug)
			window.draw(FPS);

		/* display drawing */
		window.display();
	}

	// Finish cleaning up memory, close cleanly, etc
	void Game::Finish()
	{
		window.close();
	}

	/*LuaScript* Game::newLuaScript(const std::string& file)
	{
		luaScripts.insert(std::make_pair(file, new LuaScript(file)));
		return luaScripts.find(file)->second;
	}*/

	void Game::handleLaunchOps(int c, char** args)
	{
		// launch options
		editor = false;
		debug = false;
		fullScreen = false;

		// loop through options
		int arg = 1;	// we skip arg 0 because arg 0 is the executable
		while(arg < c)
		{
			if(args[arg] == std::string("editor"))
			{
				editor = true;
			}
			else if(args[arg] == std::string("debug"))
			{
				debug = true;
			}
			else if(args[arg] == std::string("fullscreen"))
			{
				fullScreen = true;
			}
			else if(args[arg] == std::string("res"))
			{
				resolution.x = std::stoi(args[arg + 1]);
				resolution.y = std::stoi(args[arg + 1]);
				arg += 2;
			}
			else if(args[arg] == std::string("videoModes"))
			{
				logger << Logger::LogType::INFO << "Supported Fullscreen Video Modes:";

				std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
				for(std::size_t i = 0; i < modes.size(); ++i)
				{
					sf::VideoMode mode = modes[i];
					logger 	<< Logger::LogType::INFO
					        << "Mode #" + std::to_string(i) + ": " + std::to_string(mode.width) + "x" + std::to_string(mode.height)
					        + " - " + std::to_string(mode.bitsPerPixel) + " bpp";
					// ex: "Mode #0: 1920x1080 - 32 bbp"
				}
			}
			else
			{
				logger << "\nUnknown launch option: " + std::string(args[arg]) + '\n';
			}

			arg++;
		}
	}

	void Game::loadSettings(const std::string& file)
	{
		// settings file settings
		if(!settings.loadFile(file))
			logger << Logger::LogType::WARNING << "Could not open settings file, default settings will be used";
		
		settings.get("quality", graphics);
		settings.get("aa", antiAliasing);
		contextSettings.antialiasingLevel = antiAliasing;
		settings.get("fullScreen", fullScreen);
		settings.get("vertSync", verticalSync);
		settings.get("res.x", resolution.x);
		settings.get("res.y", resolution.y);
		settings.get("sound", soundLevel);
		settings.get("music", musicLevel);
	}
}
