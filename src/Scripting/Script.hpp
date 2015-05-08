#ifndef SCRIPT_HPP
#define SCRIPT_HPP

/*
 * Lua is expected to be compiled with float as lua_number!!!
 */

#include "LuaCpp/LuaCpp.hpp"

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

#include "../Settings/Settings.hpp"

#include "../KeyBindings/KeyboardManager.hpp"

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

namespace swift
{
	class AssetManager;
	class World;
	class Play;

	class Script
	{
		public:
			Script();
			virtual ~Script();

			bool loadFromFile(const std::string& file);

			void start();

			void update();

			bool load(const std::string& lfile);
			bool save(const std::string& sfile);

			bool toDelete();

			void reset();

			static void setResourcePath(const std::string& rp);

		protected:
			virtual void addVariables() = 0;
			virtual void addClasses() = 0;
			virtual void addFunctions() = 0;

			lpp::State luaState;

		private:
			std::string file;
			bool deleteMe;

			static std::string resPath;
			static std::string getResourcePath();
	};
}

#endif // SCRIPT_HPP
