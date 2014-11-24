#ifndef LUA_STATE_HPP
#define LUA_STATE_HPP

#include <lua.hpp>

#include <string>

#include "Selection.hpp"

namespace lpp
{
	class State
	{
		public:
			State();
			
			// non-copyable
			State(const State&) = delete;
			State& operator =(const State&) = delete;
			
			~State();
			
			// comparing a state to another doesn't make much sense
			bool operator ==(State&) = delete;
			
			// load a file to be called
			// Returns an error code if an error occurs (ex: syntax error)
			// the error is then pushed onto the stack, from where it can be
			// popped and read with getErrors()
			auto loadFile(const std::string& f) -> decltype(LUA_OK);
			
			// run the file.
			// Returns an error code if an error occurs
			// the error is then pushed onto the stack, from where it can be
			// popped and read with getErrors()
			auto run() -> decltype(LUA_OK);
			
			// add Lua libraries to the lua_State
			void openLib(const std::string& name, lua_CFunction open);
			
			// select a global variable
			Selection operator[](const std::string& name);
			
			// run a string of Lua code
			auto operator() (const std::string& name) -> decltype(LUA_OK);
			
			// pull from the stack an error message and return it (if one exists)
			std::string getErrors() const;
			
			// act as a lua_State
			operator lua_State*() const;
			
			// reset the Lua state
			void reload();

		private:
			void clean();

			lua_State* state;
			
			using FunctionsMap = std::unordered_map<std::string, std::unique_ptr<BaseCppFunction>>;
			
			FunctionsMap functions;
	};
}

#endif // STATE_HPP
