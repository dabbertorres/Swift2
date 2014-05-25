#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <Selene/selene.h>

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include "../GUI/Window.hpp"

namespace swift
{
	/*
	 * Each Script object expects two functions to exist in the
	 * Lua script:
	 *
	 * Start()
	 * Update()
	 *
	 * 1 variable is expected to exist:
	 * Done
	 *
	 * 'Done' should be set to false during 'Start'.
	 *
	 * Start is called during Script construction.
	 * This function should only do setup, etc.
	 *
	 * Update is called every game tick. If the state of the script
	 * should ever change, that code goes in here.
	 *
	 * Finish is called at a game tick that finds 'Done' to be true
	 */

	class AssetManager;

	class Script
	{
		public:
			Script();
			~Script();

			bool loadFromFile(const std::string& file);

			void start();

			void run();

			bool toDelete();

			template<typename T>
			void getVariable(const std::string& name, T& value);

			static void setWindow(sf::RenderWindow& win);
			static void setAssetManager(AssetManager& am);
			static void setGUI(cstr::Window& ui);

		private:
			sel::State luaState;
			bool deleteMe;

			static sf::RenderWindow* window;
			static AssetManager* assets;
			static cstr::Window* gui;
			// should have a static variable for GUIs as well. Then the GUI affected can change based on state too.
			// This will need more wrapper functions
	};

	template<typename T>
	void Script::getVariable(const std::string& name, T& value)
	{
		value = static_cast<T>(luaState[name.c_str()]);
	}
}

#endif // SCRIPT_HPP
