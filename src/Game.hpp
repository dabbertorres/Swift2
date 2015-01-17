/**
 *	Swift Engine
 *
 *	A 2D game engine aiming for speed and reliability.
 * 
 **/

#define VERSION "0.6.0-10262014"
#define AUTHOR "Alec Iverson"

#ifndef GAME_HPP
#define GAME_HPP

/* State System */
#include "StateSystem/State.hpp"
#include "StateSystem/States/Editor.hpp"
#include "StateSystem/States/Play.hpp"
#include "StateSystem/States/MainMenu.hpp"
#include "StateSystem/States/SettingsMenu.hpp"

/* Input headers */
#include "KeyBindings/KeyboardManager.hpp"
#include "KeyBindings/MouseManager.hpp"

/* Utility headers */
#include "Console/Console.hpp"
#include "Logger/Logger.hpp"
#include "Settings/Settings.hpp"

/* Resource headers */
#include "ResourceManager/AssetManager.hpp"
#include "ResourceManager/ModManager.hpp"

/* Sound headers */
#include "SoundSystem/SoundPlayer.hpp"
#include "SoundSystem/MusicPlayer.hpp"

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
			// t = title of the window/game,
			// tps = engine ticks per second
			Game(const std::string& t, unsigned tps);
			~Game();

			// Let the end user say exactly when they want the engine to commence running,
			// calling special functions and such outside of the constructor, and setting
			// launch options
			virtual void start(int c, char** args);

			// For flexibility. Want different kinds of GameLoops? Go crazy!
			// May want to add arguments of some sort to make that actually correct...
			void gameLoop();

			// Clean up, save, close data, etc. Anything that you want deleted before Game
			// gets destroyed
			void finish();

		protected:
			/* Engine */
			// Updating game logic, handling input, memory management, etc.
			// In a separate function to keep GameLoop looking clean and easier
			// to comprehend
			void update(sf::Time dt);
			
			// Handle state changes, etc
			void manageStates();
			
			// Drawing all drawable game objects, backgrounds, etc
			// Same reason as why it has it's own function as Update
			void draw(float e);
			
			// figure out settings for window and create it
			void setupWindow();
			
			// invoke asset loading
			// by default, loads the following folders:
			// data/animations
			// data/fonts
			// data/music
			// data/scripts
			// data/sounds
			// data/textures
			virtual void loadAssets();
			
			// find and load mods
			// by default, loads all mods found in:
			// data/mods
			virtual void loadMods();
			
			// start up the state system
			void initState();
			
			// initialize scripting variables
			void initScripting();
			
			virtual void addKeyboardCommands();
			
			virtual void addConsoleCommands();
			
			// handles any launch options and sets the respective variables
			virtual void handleLaunchOps(int c, char** args);
			
			// opens the settings file and sets the respective variables
			virtual void loadSettings(const std::string& file);
			
			bool running;
			sf::Font defaultFont;
			
			/* Resources */
			AssetManager assets;
			ModManager mods;
			
			/* Sound */
			SoundPlayer soundPlayer;
			MusicPlayer musicPlayer;
			
			/* Input */
			KeyboardManager keyboard;
			MouseManager mouse;
			
			/* Something about the console should go here, but I don't know what to put other than "Console". Which seems redundant */
			Console console;

			/* FPS tracking */
			sf::Text FPS;
			
			/* Settings */
			Settings settings;
			Settings controls;
			Settings dictionary;
			
			unsigned graphics;		// 0 = Low, 1 = Medium, 2 = High
			bool smoothing;			// texture smoothing
			bool fullscreen;
			bool verticalSync;
			Resolution resolution;
			unsigned soundLevel;
			unsigned musicLevel;
			std::string language;

			// random number generator
			std::mt19937 rng;	// Whenever something random is needed, this is all ready!
			
	private:
			/* Engine variables */
			sf::RenderWindow window;
			std::string title;
			
			/* States */
			State* currentState;
			
			/* timing */
			sf::Clock GameTime;		// Game loop timing. Starts once Game::Start() is called.
			float ticksPerSecond;	// Iterations of Update

			/* Launch Arguments */
			bool editor;	// for running the map editor - not in use
			bool debug;		// show debugging/performance info
	};
}

#endif // GAME_HPP
