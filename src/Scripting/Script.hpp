#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <Selene/selene.h>

#include <string>

namespace swift
{
	/*
	 * Each Script object expects three functions to exist in the
	 * Lua script:
	 * Start()
	 * Update()
	 * Finish()
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
	 
	class Script
	{
		public:
			Script();
			~Script();
			
			bool loadFromFile(const std::string& file);
			
			void run();
			
			bool toDelete();

		private:
			sel::State luaState;
			bool deleteMe;
	};
}

#endif // SCRIPT_HPP
