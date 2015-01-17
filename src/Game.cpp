#include "Game.hpp"

#include "SystemInfo/SystemInfo.hpp"

namespace swift
{
	Game::Game(const std::string& t, unsigned tps)
	:	running(false),
		console(500, 200, defaultFont, "$:"),
		graphics(Quality::Medium),
		smoothing(false),
		fullscreen(false),
		verticalSync(true),
		resolution({800, 600}),
		soundLevel(100),
		musicLevel(75),
		title(t),
		ticksPerSecond(tps)
	{
		addKeyboardCommands();
		addConsoleCommands();
		
		window.setVerticalSyncEnabled(verticalSync);
		window.setKeyRepeatEnabled(false);
		
		// get System Info
		log	<< "OS:\t\t" << getOSName() << '\n'
			<< "Version:\t" << getOSVersion() << '\n'
			<< "Arch:\t\t" << getOSArch() << '\n'
			<< "Total Mem:\t" << getTotalMem() << '\n'
			<< "CPU:\t\t" << getCPUModel() << '\n'
			<< "Video Vendor:\t" << getVideoVendor() << '\n'
			<< "Video Card:\t" << getVideoCard() << '\n'
			<< "Video Driver:\t" << getVideoDriver() << "\n\n";

		// fps display
		if(debug)
		{
			FPS.setFont(defaultFont);
			FPS.setScale(0.7, 0.7);
			FPS.setString("000.000");
			FPS.setColor(sf::Color::White);
			FPS.setPosition(window.getSize().x - (FPS.getGlobalBounds().width + 10), 10);
		}
	}

	Game::~Game()
	{
		if(currentState)
			delete currentState;
	}

	// Do any pre-game data loading
	// Such as setting up the scripting virtual machine
	// and setting game quality settings.
	// That's about it
	/*void Game::start(int c, char** args)
	{
		// c is the total arguments
		// args is the arguments

		// loads settings from the settings file
		loadSettings("./data/settings.ini");

		handleLaunchOps(c, args);
		
		// loads a dictionary
		dictionary.loadFile("./data/dictionaries/" + language + ".dic");
		
		setupWindow();
		
		//window.setIcon(SwiftEngineIcon.width, SwiftEngineIcon.height, SwiftEngineIcon.pixel_data);	// need to figure out icon stuff
		
		loadAssets();
		
		loadMods();
		
		// gotta set this if you want any text to display
		defaultFont = assets.getFont("./data/fonts/segoeuisl.ttf");

		initState();
		
		initScripting();
	}*/

	void Game::gameLoop()
	{
		running = true;
		
		const sf::Time dt = sf::seconds(1.f / ticksPerSecond);

		sf::Time currentTime = GameTime.getElapsedTime();
		sf::Time lag = sf::seconds(0);

		while(running)
		{
			sf::Time newTime = GameTime.getElapsedTime();
			sf::Time frameTime = newTime - currentTime;

			if(frameTime > sf::seconds(0.25))
				frameTime = sf::seconds(0.25);

			currentTime = newTime;

			lag += frameTime;

			while(lag >= dt)
			{
				update(dt);
				lag -= dt;
			}

			draw(lag.asSeconds() / dt.asSeconds());
			
			// frames per second measurement
			if(debug)
				FPS.setString(std::to_string(1 / frameTime.asSeconds()).substr(0, 7));
		}
	}

	// Finish cleaning up memory, close cleanly, etc
	void Game::finish()
	{
		window.close();
	}

	void Game::update(sf::Time dt)
	{
		sf::Event event;
		while(window.pollEvent(event) && running)
		{
			keyboard(event);
			mouse(event);

			// avoid having the console type the key that toggles it
			if(event.type == sf::Event::TextEntered && event.text.unicode != '\\')
				console.update(event);

			if(event.type == sf::Event::Closed)
				running = false;
			
			if(running)
				currentState->handleEvent(event);
		}
		
		if(running)
		{
			currentState->update(dt);
			manageStates();
		}
	}

	void Game::manageStates()
	{
		if(currentState->switchFrom())
		{
			State::Type nextState = currentState->finish();
			delete currentState;
			currentState = nullptr;

			switch(nextState)
			{
				case State::Type::MainMenu:
					currentState = new MainMenu(window, assets, soundPlayer, musicPlayer, settings, dictionary);
					break;
				case State::Type::SettingsMenu:
					currentState = new SettingsMenu(window, assets, soundPlayer, musicPlayer, settings, dictionary);
					break;
				case State::Type::Play:
					currentState = new Play(window, assets, soundPlayer, musicPlayer, settings, dictionary);
					break;
				case State::Type::Exit:
					running = false;
					break;
				default:
					log << "[ERROR]: State machine error, state not valid\n";
					running = false;
					break;
			}
			
			if(running)
				currentState->setup();
		}
	}

	void Game::draw(float e)
	{
		if(running)
		{
			/* clear display */
			window.clear();

			/* state drawing */
			currentState->draw(e);
			
			/* other drawing */
			window.draw(console);
			
			if(debug)
				window.draw(FPS);

			/* display drawing */
			window.display();
		}
	}
	
	void Game::setupWindow()
	{
		if(fullscreen)
			window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
		else
			window.create({resolution.x, resolution.y, 32}, title, sf::Style::Titlebar | sf::Style::Close);
	}
	
	void Game::loadAssets()
	{
		assets.setSmooth(smoothing);
		assets.loadResourceFolder("./data/animations");
		assets.loadResourceFolder("./data/textures");
		assets.loadResourceFolder("./data/fonts");
		assets.loadResourceFolder("./data/music");
		assets.loadResourceFolder("./data/scripts");
		assets.loadResourceFolder("./data/sounds");
		
		// make log file a little prettier
		log << '\n';
	}
	
	void Game::loadMods()
	{
		// find all mods
		mods.loadMods("./data/mods");

		// this would be where you normally conditionally load up mods
		for(auto& m : mods.getMods())
		{
			assets.loadMod(m.second.mod);
		}
	}
	
	void Game::initState()
	{
		// state setup
		if(!editor)
			currentState = new MainMenu(window, assets, soundPlayer, musicPlayer, settings, dictionary);
		else
			currentState = new Editor(window, assets, soundPlayer, musicPlayer, settings, dictionary);
		
		currentState->setup();
	}
			
	// initialize scripting variables
	void Game::initScripting()
	{
		// setup Script static variables
		Script::setWindow(window);
		Script::setAssetManager(assets);
		Script::setClock(GameTime);
		Script::setSettings(settings);
	}
	
	void Game::addKeyboardCommands()
	{
		// add some default keybindings
		keyboard.newBinding("toggleTerminal", sf::Keyboard::BackSlash, [&]()
		{
			console.activate(!console.isActivated());
		});
	}
	
	void Game::addConsoleCommands()
	{
		// add some console commands
		console.addCommand("hello", [&](ArgVec /*args*/)
		{
			console << "\nHello to you too!";
			return 0;
		});
		
		console.addCommand("fps", [&](ArgVec /*args*/)
		{
			console << "\n" << FPS.getString();
			return 0;
		});

		console.addCommand("exit", [&](ArgVec /*args*/)
		{
			running = false;
			return 0;
		});
	}

	void Game::handleLaunchOps(int c, char** args)
	{
		// launch options
		editor = false;
		debug = false;
		fullscreen = false;

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
				fullscreen = true;
			}
			else if(args[arg] == std::string("res"))
			{
				resolution.x = std::stoi(args[arg + 1]);
				resolution.y = std::stoi(args[arg + 2]);
				arg += 2;
			}
			else if(args[arg] == std::string("videoModes"))
			{
				log << "Supported Fullscreen Video Modes:\n";

				std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
				for(std::size_t i = 0; i < modes.size(); ++i)
				{
					sf::VideoMode mode = modes[i];
					log << "Mode #" << i << ": " << mode.width << "x" << mode.height << " - " << mode.bitsPerPixel << " bpp\n";
					// ex: "Mode #0: 1920x1080 - 32 bbp"
				}
				log << '\n';
			}
			else
			{
				log << "\nUnknown launch option: " << args[arg] << '\n';
			}

			arg++;
		}
	}
	
	void Game::loadSettings(const std::string& file)
	{
		// settings file settings
		if(!settings.loadFile(file))
			log << "Could not open settings file, default settings will be used\n";

		settings.get("fullscreen", fullscreen);
		settings.get("vsync", verticalSync);
		settings.get("res.x", resolution.x);
		settings.get("res.y", resolution.y);
		settings.get("sound", soundLevel);
		settings.get("music", musicLevel);
		settings.get("lang", language);
	}
}
