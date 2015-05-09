#include "Game.hpp"

#include "SystemInfo/SystemInfo.hpp"

#ifdef __linux__
	#include <unistd.h>
#elif _WIN32
	#include <windows.h>
#endif

#include <limits.h>

namespace swift
{
	Game::Game(const std::string& t, unsigned tps)
	:	running(false),
		console(500, 200, defaultFont, "$:"),
		graphics(Quality::Medium),
		smoothing(false),
		fullscreen(false),
		verticalSync(true),
		resolution( {800, 600}),
		soundLevel(100),
		musicLevel(75),
		title(t),
		ticksPerSecond(tps),
		editor(false),
		debug(false)
	{
		addKeyboardCommands();
		addConsoleCommands();

		// get System Info
		log	<< "OS:\t\t" << getOSName() << '\n'
			<< "Version:\t" << getOSVersion() << '\n'
			<< "Arch:\t\t" << getOSArch() << '\n'
			<< "Total Mem:\t" << getTotalMem() << '\n'
			<< "CPU:\t\t" << getCPUModel() << '\n'
			<< "Video Vendor:\t" << getVideoVendor() << '\n'
			<< "Video Card:\t" << getVideoCard() << '\n'
			<< "Video Driver:\t" << getVideoDriver() << "\n\n";
		
		getResourcePath();

		Script::setResourcePath(path);
	}

	Game::~Game()
	{
		window.close();
	}

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
			{
				frameTime = sf::seconds(0.25);
			}

			currentTime = newTime;

			lag += frameTime;

			while(lag >= dt)
			{
				manageStates();
				update(dt);
				lag -= dt;
			}

			draw(lag.asSeconds() / dt.asSeconds());

			// frames per second measurement
			if(debug)
			{
				FPS.setString(std::to_string(1 / frameTime.asSeconds()).substr(0, 7));
			}
		}
	}

	const std::string& Game::getResourcePath()
	{
		if(path.empty())
		{
			char buffer[PATH_MAX];

			#ifdef __linux__
				readlink("/proc/self/exe", buffer, PATH_MAX);
			#elif _WIN32
				GetModuleFileName(NULL, buffer, PATH_MAX);
			#endif

			path = buffer;
			path = path.substr(0, path.find_last_of('/') + 1);
			path += "../data/";
		}

		return path;
	}

	void Game::update(const sf::Time& dt)
	{
		sf::Event event;

		while(window.pollEvent(event) && running)
		{
			keyboard(event);
			mouse(event);

			// avoid having the console type the key that toggles it
			if(event.type == sf::Event::TextEntered && event.text.unicode != '\\')
			{
				console.update(event);
			}

			if(event.type == sf::Event::Closed)
			{
				running = false;
			}

			if(running)
			{
				states.read()->handleEvent(event);
			}
		}

		if(running)
		{
			states.read()->update(dt);
		}
	}

	void Game::manageStates()
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

	void Game::draw(float e)
	{
		if(running)
		{
			/* clear display */
			window.clear();

			/* state drawing */
			states.read()->draw(e);

			/* other drawing */
			window.draw(console);

			if(debug)
			{
				window.draw(FPS);
			}

			/* display drawing */
			window.display();
		}
	}

	void Game::setupWindow()
	{
		if(fullscreen)
		{
			window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
		}
		else
			window.create( {resolution.x, resolution.y, 32}, title, sf::Style::Titlebar | sf::Style::Close);

		window.setVerticalSyncEnabled(verticalSync);
		window.setKeyRepeatEnabled(false);

		// fps display
		FPS.setFont(defaultFont);
		FPS.setScale(0.7, 0.7);
		FPS.setString("000.000");
		FPS.setColor(sf::Color::White);
		FPS.setPosition(window.getSize().x - (FPS.getGlobalBounds().width + 10), 10);
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
		{
			log << "Could not open settings file, default settings will be used\n";
		}

		settings.get("fullscreen", fullscreen);
		settings.get("vsync", verticalSync);
		settings.get("res.x", resolution.x);
		settings.get("res.y", resolution.y);
		settings.get("sound", soundLevel);
		settings.get("music", musicLevel);
		settings.get("lang", language);
	}
}
