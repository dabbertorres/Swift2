#ifndef SCRIPT_HPP
#define SCRIPT_HPP

/*
 * Lua is expected to be compiled with float as lua_number!!!
 */

#include "LNA/LNA.hpp"

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
		friend class ScriptSave;
		
		public:
			Script();
			Script(const Script& other);
			
			virtual ~Script() = default;

			bool loadFromFile(const std::string& lfile);

			void start();

			void update();

			bool isDone() const;

			void reset();
			
			const std::string& getFile() const;

			static void setResourcePath(const std::string& rp);

		protected:
			virtual void addVariables()
			{}
			
			virtual void addClasses()
			
			{}
			
			virtual void addFunctions()
			{}

			lna::State luaState;

		private:
			std::string file;
			bool done;

			static std::string resPath;
			static std::string getResourcePath();
	};
	
	using ScriptHandle = std::unique_ptr<Script>;
}

#endif // SCRIPT_HPP
