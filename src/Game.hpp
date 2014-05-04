/**
 *	Swift Engine
 *
 *	A 2D game engine aiming for speed and reliability.
 * 
 **/

#define VERSION "0.2.1-020414"
#define AUTHOR "Alec Iverson"

#ifndef GAME_HPP
#define GAME_HPP

/* C++ headers */
// standards
#include <cstdlib>
#include <cctype>
#include <cmath>

// input/output
#include <iostream>
#include <fstream>

// containers
#include <vector>
#include <map>

// multithreading
//#include <thread>
//#include <mutex>

// misc
#include <string>
#include <utility>
#include <chrono>
#include <random>

/* POSIX headers */
#include <dirent.h>

/* SFML headers */
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/* State System */
#include "StateSystem/State.hpp"
#include "StateSystem/States/Play.hpp"
#include "StateSystem/States/MainMenu.hpp"

/* Lua headers */
#include "Scripting/Script.hpp"

/* Input headers */
#include "KeyBindings/KeyboardManager.hpp"
#include "KeyBindings/MouseManager.hpp"

/* GUI headers */
#include "GUI/Window.hpp"
#include "GUI/Widgets.hpp"

/* Utility headers */
#include "Console/Console.hpp"
#include "Logger/Logger.hpp"
#include "Settings/Settings.hpp"

/* Resource headers */
#include "ResourceManager/AssetManager.hpp"
#include "ResourceManager/ModManager.hpp"

namespace swift
{	
	namespace Quality
	{
		const unsigned Low = 0;
		const unsigned Medium = 1;
		const unsigned High = 2;
	};
	
	// Easy collection of data
	struct Resolution
	{
		unsigned x;
		unsigned y;
	};

	class Game
	{
		public:
			// A default constructor is fine for now, may want to add a constructor
			// that accepts command line arguments at some point, for example,
			// enabling use of that map editor I want to do.
			Game();
			~Game();

			// Let the end user say exactly when they want the engine to commence running,
			// calling special functions and such outside of the constructor, and setting
			// launch options
			void Start(int c, char** args);

			// For flexibility. Want different kinds of GameLoops? Go crazy!
			// May want to add arguments of some sort to make that actually correct...
			void GameLoop();

			// Clean up, save, close data, etc. Anything that you want deleted before Game
			// gets destroyed
			void Finish();

		private:
			/* Engine */
			// Updating game logic, handling input, memory management, etc.
			// In a separate function to keep GameLoop looking clean and easier
			// to comprehend
			void Update(sf::Time dt);
			
			// Drawing all drawable game objects, backgrounds, etc
			// Same reason as why it has it's own function as Update
			void Draw(float e);
			
			// handles any launch options and sets the respective variables
			void handleLaunchOps(int c, char** args);
			
			// opens the settings file and sets the respective variables
			void loadSettings(const std::string& file);

			/* Engine variables */
			sf::RenderWindow window;
			bool running;				// The game is running or not, for continuing/ending the game loop
			sf::Font defaultFont;
			
			/* Resource Managers */
			AssetManager assets;
			ModManager mods;
			
			/* States */
			State* currentState;
			Play play;
			MainMenu mainMenu;
			
			/* Input */
			KeyboardManager keyboard;
			MouseManager mouse;
			
			/* Debug */
			Logger logger;
			Console console;

			/* FPS tracking */
			float fps;
			sf::Text FPS;
			
			/* Settings */
			sf::ContextSettings contextSettings;
			Settings settings;
			
			unsigned graphics;		// 0 = Low, 1 = Medium, 2 = High
			unsigned antiAliasing;	// 
			bool fullScreen;
			bool verticalSync;		// Sir, would you like some Vertical Synchronization with those frames?
			Resolution resolution;
			unsigned soundLevel;
			unsigned musicLevel;

			// random number generator
			std::mt19937 randomNumberGenerator;	// Whenever something random is needed, this is all ready!

			/* timing */
			sf::Clock GameTime;		// Game loop timing. Starts once Game::Start() is called.
			int framesPerSecond;	// Iterations of the GameLoop.
			float ticksPerSecond;		// Iterations of Update

			/* Launch Arguments */
			bool editor;	// for running the "map" editor - not in use
			bool debug;		// show debugging/performance info
	};
}

#endif // GAME_HPP
