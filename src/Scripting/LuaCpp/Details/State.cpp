#include "State.hpp"

namespace lpp
{
	State::State()
	{
		state = luaL_newstate();
	}

	State::~State()
	{
		lua_settop(state, 0);
		lua_close(state);
	}
	
	auto State::loadFile(const std::string& f) -> decltype(LUA_OK)
	{
		return luaL_loadfile(state, f.c_str());
	}
	
	auto State::run() -> decltype(LUA_OK)
	{
		return lua_pcall(state, 0, 0, 0);
	}
	
	void State::openLib(const std::string& name, lua_CFunction open)
	{
		luaL_requiref(state, name.c_str(), open, 1);
		clean();
	}
	
	Selection State::operator[](const std::string& name)
	{
		return Selection(state, name, functions);
	}
	
	Selection State::operator[](int idx)
	{
		int top = lua_gettop(state);
		
		if(top != 0 && std::abs(idx) <= top)
			return Selection(state, "", functions, idx);
		else
			return Selection(state, "", functions);
	}
	
	unsigned int State::getTop() const
	{
		return lua_gettop(state);
	}
	
	void State::call(const std::string& func, int nargs)
	{
		// put everything in the right order
		lua_getglobal(state, func.c_str());
		
		for(int i = -(nargs + 1); i < -1; i++)
		{
			lua_pushvalue(state, i);
		}
		
		// get to it
		if(lua_pcall(state, nargs, 0, 0) != LUA_OK)
		{
			std::size_t size;
			const char* buff = lua_tolstring(state, -1, &size);
			std::string msg = {buff, size};
			luaL_error(state, msg.c_str());
		}
		
		// clean up
		lua_pop(state, nargs);
	}
	
	auto State::operator()(const std::string& name) -> decltype(LUA_OK)
	{
		luaL_loadstring(state, name.c_str());
		return lua_pcall(state, 0, 0, 0);
	}
	
	std::string State::getErrors() const
	{
		std::string msg = "";
		
		if(!lua_isnone(state, -1))
		{
			std::size_t size;
			const char* buff = lua_tolstring(state, -1, &size);
			msg = {buff, size};
		}
		
		lua_pop(state, 1);
		return msg;
	}
	
	State::operator lua_State*() const
	{
		return state;
	}
	
	void State::reload()
	{
		lua_close(state);
		state = luaL_newstate();
		functions.clear();
	}
	
	void State::clean()
	{
		lua_settop(state, 0);
	}
}
