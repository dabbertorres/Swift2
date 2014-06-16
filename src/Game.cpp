#include "Game.hpp"

#include "SystemInfo/SystemInfo.hpp"

namespace swift
{
	const std::string errorLog = "./data/log.txt";

	Game::Game()
		:	logger("Alpha", errorLog),
		    console(500, 200, defaultFont, "[swift2]:")
	{
		graphics = Quality::Medium;
		smoothing = false;
		verticalSync = true;
		fullScreen = false;
		resolution.x = 800;
		resolution.y = 600;
		running = false;

		// engine integral settings
		ticksPerSecond = 60;
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
	void Game::Start(int c, char** args)
	{
		// c is the total arguments
		// args is the arguments

		// loads settings from the settings file
		loadSettings("./data/settings/settings.ini");

		handleLaunchOps(c, args);

		// Window set up.
		if(fullScreen)
			window.create(sf::VideoMode(resolution.x, resolution.y, 32), "Swift Engine", sf::Style::Fullscreen, contextSettings);
		else
			window.create(sf::VideoMode(resolution.x, resolution.y, 32), "Swift Engine", sf::Style::Titlebar | sf::Style::Close, contextSettings);
		
		// get System Info
		logger	<< "OS:\t\t" << getOSName() << '\n'
				<< "Version:\t" << getOSVersion() << '\n'
				<< "Arch:\t\t" << getOSArch() << '\n'
				<< "Total Mem:\t" << getTotalMem() << '\n'
				<< "CPU:\t\t" << getCPUModel() << '\n'
				<< "Video Vendor:\t" << getVideoVendor() << '\n'
				<< "Video Card:\t" << getVideoCard() << '\n'
				<< "Video Driver:\t" << getVideoDriver() << '\n';
		
		//window.setIcon(SwiftEngineIcon.width, SwiftEngineIcon.height, SwiftEngineIcon.pixel_data);
		window.setVerticalSyncEnabled(verticalSync);
		window.setKeyRepeatEnabled(false);

		assets.setSmooth(smoothing);
		assets.loadResourceFolder("./data/fonts");
		assets.loadResourceFolder("./data/textures");
		assets.loadResourceFolder("./data/music");
		assets.loadResourceFolder("./data/scripts");
		assets.loadResourceFolder("./data/skeletons");
		assets.loadResourceFolder("./data/sounds");

		mods.loadMods("./data/mods");

		for(auto &m : mods.getMods())
		{
			assets.loadMod(m.second.mod);
		}
		
		defaultFont = assets.getFont("./data/fonts/DroidSansMono.ttf");

		// add some default keybindings
		keyboard.newBinding("toggleTerminal", sf::Keyboard::BackSlash, [&]()
		{
			console.activate(!console.isActivated());
		});

		// add some console commands
		console.addCommand("hello", [](ArgVec /*args*/)
		{
			return "Hello to you too!";
		});

		console.addCommand("exit", [&](ArgVec /*args*/)
		{
			running = false;
			return "Exiting";
		});

		running = true;

		// fps display
		if(debug)
		{
			FPS.setFont(defaultFont);
			FPS.setScale(0.7, 0.7);
			FPS.setString("000.000");
			FPS.setColor(sf::Color::White);
			FPS.setPosition(window.getSize().x - (FPS.getGlobalBounds().width + 2), 10);
			std::cerr << FPS.getPosition().x << ' ' << FPS.getPosition().y << '\n';
		}

		// setup Script static variables
		Script::setWindow(window);
		Script::setAssetManager(assets);
		Script::setClock(GameTime);

		// state setup
		currentState = new MainMenu(window, assets);
		currentState->setup();
	}

	void Game::GameLoop()
	{
		const sf::Time dt = sf::seconds(1 / ticksPerSecond);

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
				Update(dt);
				lag -= dt;
			}

			Draw(lag.asSeconds() / dt.asSeconds());
		}
	}

	void Game::Update(sf::Time dt)
	{
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

			currentState->handleEvent(event);
		}

		if(debug)
			FPS.setString(std::to_string(1 / dt.asSeconds()).substr(0, 7));

		currentState->update(dt);
		manageStates();
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
					currentState = new MainMenu(window, assets);
					currentState->setup();
					break;
				case State::Type::SettingsMenu:
					currentState = new SettingsMenu(window, assets);
					currentState->setup();
					break;
				case State::Type::Play:
					currentState = new Play(window, assets);
					currentState->setup();
					break;
				case State::Type::Exit:
					running = false;
					break;
			}
		}
	}

	void Game::Draw(float e)
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

	// Finish cleaning up memory, close cleanly, etc
	void Game::Finish()
	{
		window.close();
	}

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
				logger << Logger::LogType::INFO << "Supported Fullscreen Video Modes:\n";

				std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
				for(std::size_t i = 0; i < modes.size(); ++i)
				{
					sf::VideoMode mode = modes[i];
					logger 	<< Logger::LogType::INFO
					        << "Mode #" + std::to_string(i) + ": " + std::to_string(mode.width) + "x" + std::to_string(mode.height)
					        + " - " + std::to_string(mode.bitsPerPixel) + " bpp\n";
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
			logger << Logger::LogType::WARNING << "Could not open settings file, default settings will be used\n";

		settings.get("quality", graphics);
		settings.get("fullScreen", fullScreen);
		settings.get("vertSync", verticalSync);
		settings.get("res.x", resolution.x);
		settings.get("res.y", resolution.y);
		settings.get("sound", soundLevel);
		settings.get("music", musicLevel);
	}
}
