/**
 *	Swift Engine
 *
 *	A 2D game engine aiming for speed and reliability.
 *
 **/

#ifndef SWIFT_GAME_HPP
#define SWIFT_GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/Window/Event.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>

#include "FileSystem/gfs.hpp"

#include "Logger/Logger.hpp"

namespace swift
{
	class Game
	{
		public:
			// t = title of the window/game,
			// tps = engine ticks per second
			Game(const std::string& t, unsigned tps);
			virtual ~Game();

			// Let the user choose when to start
			// creates the window, and then starts "gameLoop"
			void start();
			
			const gfs::Path& getResourcePath();
			
		protected:
			bool running;
			
			sf::Font defaultFont;
			
			sf::Text fps;
			
			sf::Clock gameTime;
			
			// engine settings
			bool fullscreen;
			bool verticalSync;
			sf::Vector2u resolution;
			
			sf::RenderWindow window;

		private:
			// the thing that makes the game actually run!
			// calls manageStates
			virtual void gameLoop();
			
			// handling events and input
			// calls "gameHandleEvents"
			virtual void handleEvents();
			
			// Updating game logic
			// calls "gameUpdate"
			virtual void update(const sf::Time& dt);

			// Drawing all drawable game objects, backgrounds, etc
			// calls "gameDraw"
			virtual void draw();
			
			virtual void gameHandleEvents(const sf::Event& event) = 0;
			virtual void gameUpdate(const sf::Time& dt) = 0;
			virtual void manageStates() = 0;
			virtual void gameDraw() = 0;
			
			virtual void setupWindow();
			
			std::string title;

			gfs::Path resourcePath;

			float ticksPerSecond;	// calls to update(const sf::Time& dt) per second
	};
}

#endif // SWIFT_GAME_HPP
