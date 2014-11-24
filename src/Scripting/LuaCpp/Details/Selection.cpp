#include "Selection.hpp"

namespace lpp
{
	Selection::Selection(lua_State* s, const std::string& n, FunctionsMap& funcs)
	:	state(s),
		name(n),
		index(0),
		functions(funcs)
	{}
	
	Selection::Selection(lua_State* s, const std::string& n, FunctionsMap& funcs, int idx)
	:	state(s),
		name(n),
		index(idx),
		functions(funcs)
	{}

	Selection::~Selection()
	{
		lua_settop(state, 0);
	}
	
	/* Selection operators */
	Selection Selection::operator [](const std::string& n) const
	{
		if(index == 0)
			lua_getglobal(state, name.c_str());
		
		std::string newName = name + '.' + n;
		
		if(!lua_istable(state, -1))
			luaL_error(state, "Value on top of stack is not a table");
		
		lua_pushlstring(state, n.c_str(), n.size());
		lua_rawget(state, -2);
		
		return Selection(state, newName, functions, -1);
	}
	
	Selection Selection::operator [](const int i) const
	{
		if(index == 0)
			lua_getglobal(state, name.c_str());
			
		std::string newName = name + '[' + std::to_string(i) + ']';
		
		if(!lua_istable(state, -1))
			luaL_error(state, "Value on top of stack is not a table");
		
		lua_rawgeti(state, -1, i);
		
		return Selection(state, newName, functions, -1);
	}
}
