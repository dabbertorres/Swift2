#include "Class.hpp"

namespace lpp
{
	Class::Class(lua_State* s, const std::string& n)
	:	state(s)
	{
		std::string name = n + "_lib";
		luaL_newmetatable(state, name.c_str());
	}

	Class::~Class()
	{
	}
}
