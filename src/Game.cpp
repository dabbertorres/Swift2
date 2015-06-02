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
		
		while(running)
		{
			sf::Time newTime = gameTime.getElapsedTime();
			sf::Time frameTime = newTime - lastTime;
			
			if(frameTime > sf::seconds(0.25))
			{
				frameTime = sf::seconds(0.25);
			}
			
			lastTime = newTime;
			
			lag += frameTime;
			
			while(lag >= dt && running)
			{
				update(dt);
				manageStates();
				handleEvents();
				lag -= dt;
			}
			
			if(running)
			{
				draw();
			}
			
#ifdef DEBUG
			// frames per second measurement
			fps.setString(std::to_string(1.f / frameTime.asSeconds()).substr(0, 5));
#endif
		}
	}
	
	void Game::handleEvents()
	{
		sf::Event event;

		while(window.pollEvent(event) && running)
		{
			gameHandleEvents(event);
			
			if(event.type == sf::Event::Closed)
			{
				running = false;
			}
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
