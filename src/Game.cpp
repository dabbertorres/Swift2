#include "Game.hpp"

#include "SystemInfo/SystemInfo.hpp"

namespace swift
{
	Game::Game(const std::string& t, unsigned tps)
		:	running(false),
			title(t),
			console(500, 200, defaultFont, "$:"),
			graphics(Quality::Medium),
			smoothing(true),
			fullscreen(false),
			verticalSync(true),
			resolution({800, 600}),
			soundLevel(100),
			musicLevel(75),
			ticksPerSecond(tps)
	{
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
	void Game::start(int c, char** args)
	{
		// c is the total arguments
		// args is the arguments

		// loads settings from the settings file
		loadSettings("./data/settings.ini");

		handleLaunchOps(c, args);
		
		// loads a dictionary
		log << "Loading language: " << language + ".dic\n";
		dictionary.loadFile("./data/dictionaries/" + language + ".dic");

		// Window set up.
		if(fullscreen)
			window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
		else
			window.create({resolution.x, resolution.y, 32}, title, sf::Style::Titlebar | sf::Style::Close);
		
		// get System Info
		log	<< "OS:\t\t" << getOSName() << '\n'
			<< "Version:\t" << getOSVersion() << '\n'
			<< "Arch:\t\t" << getOSArch() << '\n'
			<< "Total Mem:\t" << getTotalMem() << '\n'
			<< "CPU:\t\t" << getCPUModel() << '\n'
			<< "Video Vendor:\t" << getVideoVendor() << '\n'
			<< "Video Card:\t" << getVideoCard() << '\n'
			<< "Video Driver:\t" << getVideoDriver() << "\n\n";
		
		//window.setIcon(SwiftEngineIcon.width, SwiftEngineIcon.height, SwiftEngineIcon.pixel_data);
		window.setVerticalSyncEnabled(verticalSync);
		window.setKeyRepeatEnabled(false);

		assets.setSmooth(smoothing);
		assets.loadResourceFolder("./data/animations");
		assets.loadResourceFolder("./data/textures");
		assets.loadResourceFolder("./data/fonts");
		assets.loadResourceFolder("./data/music");
		assets.loadResourceFolder("./data/scripts");
		assets.loadResourceFolder("./data/skeletons");
		assets.loadResourceFolder("./data/sounds");
		
		log << '\n';

		mods.loadMods("./data/mods");

		for(auto& m : mods.getMods())
		{
			assets.loadMod(m.second.mod);
		}
		
		defaultFont = assets.getFont("./data/fonts/segoeuisl.ttf");

		running = true;

		// fps display
		if(debug)
		{
			FPS.setFont(defaultFont);
			FPS.setScale(0.7, 0.7);
			FPS.setString("000.000");
			FPS.setColor(sf::Color::White);
			FPS.setPosition(window.getSize().x - (FPS.getGlobalBounds().width + 10), 10);
		}

		// setup Script static variables
		Script::setWindow(window);
		Script::setAssetManager(assets);
		Script::setClock(GameTime);
		Script::setSettings(settings);
		Script::setLogger(log);

		// state setup
		currentState = new MainMenu(window, assets, settings, dictionary);
		currentState->setup();
	}

	void Game::gameLoop()
	{
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
		if(running)
			manageStates();
		
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
			currentState->update(dt);
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
					currentState = new MainMenu(window, assets, settings, dictionary);
					break;
				case State::Type::SettingsMenu:
					currentState = new SettingsMenu(window, assets, settings, dictionary);
					break;
				case State::Type::Play:
					currentState = new Play(window, assets, settings, dictionary);
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
