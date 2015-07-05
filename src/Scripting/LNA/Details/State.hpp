#ifndef LUA_STATE_HPP
#define LUA_STATE_HPP

#include <lua.hpp>

#include <string>

#include "Selection.hpp"

namespace lna
{
	class State
	{
		public:
			State();
			
			// non-copyable
			State(const State&) = delete;
			State& operator=(const State&) = delete;
			
			~State();
			
			// comparing a state to another doesn't make much sense
			bool operator==(State&) = delete;
			
			// load a file to be called
			// Returns an error code if an error occurs (ex: syntax error)
			// the error is then pushed onto the stack, from where it can be
			// popped and read with getErrors()
			decltype(LUA_OK) loadFile(const std::string& f);
			
			// run the file.
			// Returns an error code if an error occurs
			// the error is then pushed onto the stack, from where it can be
			// popped and read with getErrors()
			decltype(LUA_OK) run();
			
			// add Lua libraries to the lua_State
			void openLib(const std::string& name, const lua_CFunction& open);
			
			// select a global variable
			Selection operator[](const std::string& name);
			
			// select a variable off the stack
			Selection operator[](int idx);
			
			// get the number of elements on the stack
			int getTop() const;
			
			// run a string of Lua code
			decltype(LUA_OK) operator()(const std::string& name);
			
			// pull from the stack an error message and return it (if one exists)
			std::string getErrors() const;
			
			// act as a lua_State
			operator lua_State*() const;
			
			// reset the Lua state
			void reload();
			
			void clean();

		private:
			lua_State* state;
			
			Functions functions;
	};
	
	inline State::State()
	{
		state = luaL_newstate();
	}

	inline State::~State()
	{
		lua_settop(state, 0);
		lua_close(state);
	}
	
	inline decltype(LUA_OK) State::loadFile(const std::string& f)
	{
		return luaL_loadfile(state, f.c_str());
	}
	
	inline decltype(LUA_OK) State::run()
	{
		return lua_pcall(state, 0, 0, 0);
	}
	
	inline void State::openLib(const std::string& name, const lua_CFunction& open)
	{
#if LUA_VERSION_NUM >= 502
		luaL_requiref(state, name.c_str(), open, 1);
#else
		lua_pushcfunction(state, open);
		lua_pcall(state, 0, 0, 0);
#endif
		clean();
	}
	
	inline Selection State::operator[](const std::string& name)
	{
		return Selection(state, name, functions);
	}
	
	inline Selection State::operator[](int idx)
	{
		int top = lua_gettop(state);
		
		if(top != 0 && std::abs(idx) <= top)
			return Selection(state, "", functions, idx);
		else
		{
			luaL_error(state, "Stack is empty!");
			return Selection(state, "", functions, 0);
		}
	}
	
	inline int State::getTop() const
	{
		return lua_gettop(state);
	}
	
	inline decltype(LUA_OK) State::operator()(const std::string& name)
	{
		luaL_loadstring(state, name.c_str());
		return lua_pcall(state, 0, 0, 0);
	}
	
	inline std::string State::getErrors() const
	{
		std::string msg = "";
		
		if(!lua_isnone(state, -1))
		{
			std::size_t size;
			const char* buff = luaL_checklstring(state, -1, &size);
			msg = {buff, size};
		}
		
		lua_pop(state, 1);
		return msg;
	}
	
	inline State::operator lua_State*() const
	{
		return state;
	}
	
	inline void State::reload()
	{
		clean();
		lua_close(state);
		state = luaL_newstate();
		functions.clear();
	}
	
	inline void State::clean()
	{
		lua_settop(state, 0);
	}
}

#endif // STATE_HPP
