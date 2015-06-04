#include "Game.hpp"

namespace swift
{
	Game::Game(const std::string& t, unsigned tps)
	:	running(false),
		fullscreen(false),
		resolution({800, 600}),
		title(t),
		ticksPerSecond(tps)
	{
		getResourcePath();
	}

	Game::~Game()
	{
		window.close();
	}
	
	void Game::start()
	{
		setupWindow();
		gameLoop();
	}
	
	void Game::setTitle(const std::string& t)
	{
		title = t;
		window.setTitle(title);
	}
	
	const gfs::Path& Game::getResourcePath()
	{
		if(!resourcePath)
		{
			resourcePath = gfs::selfPath().parent() / "../data";
			Logger::get() << "Resource Path: " << resourcePath << '\n';
		}
		
		return resourcePath;
	}
	
	void Game::gameLoop()
	{
		running = true;
		
		const sf::Time dt = sf::seconds(1.f / ticksPerSecond);
		
		sf::Time lastTime = gameTime.getElapsedTime();
		sf::Time lag = sf::seconds(0);
		
#ifdef DEBUG
		const float FRAMES_TO_TIME = 60.f;
		sf::Clock framesClock;
		unsigned int frameCounter = 0;
#endif
		
		while(running)
		{
			sf::Time newTime = gameTime.getElapsedTime();
			sf::Time frameTime = newTime - lastTime;
			
			lastTime = newTime;
			
			lag += frameTime;
			
			while(lag >= dt)
			{
				handleEvents();
				update(dt);
				lag -= dt;
			}
			
			draw();
			
#ifdef DEBUG
			// frames per second measurement
			frameCounter++;
			
			if(frameCounter >= FRAMES_TO_TIME)
			{
				fps.setString(std::to_string(FRAMES_TO_TIME / framesClock.restart().asSeconds()).substr(0, 8));
				frameCounter = 0;
			}
#endif
			
			// make state changes last, since they affect everything else
			manageStates();
		}
	}
	
	void Game::handleEvents()
	{
		sf::Event event;

		while(window.pollEvent(event))
		{
			gameHandleEvents(event);
		}
	}

	void Game::update(const sf::Time& dt)
	{
		gameUpdate(dt);
	}

	void Game::draw()
	{
		window.clear();
		
		// let game draw
		gameDraw();
		
#ifdef DEBUG
		window.draw(fps);
#endif
		
		window.display();
	}

	void Game::setupWindow()
	{
		if(fullscreen)
		{
			window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen);
		}
		else
		{
			window.create({resolution.x, resolution.y}, title, sf::Style::Titlebar | sf::Style::Close);
		}
		
		window.setVerticalSyncEnabled(verticalSync);
		window.setKeyRepeatEnabled(false);

		fps.setFont(defaultFont);
		fps.setColor(sf::Color::White);
		fps.setPosition(5, 5);
	}
}
