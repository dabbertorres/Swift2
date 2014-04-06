#include "Script.hpp"

namespace swift
{
	Script::Script(const std::string& file)
	{
		deleteMe = false;
		
		luaState.Load(file);
		
		// We don't want to give the scripts access to os commands or file writing
		luaState.OpenLib("base", luaopen_base);
		luaState.OpenLib("math", luaopen_math);
		luaState.OpenLib("string", luaopen_string);
		luaState.OpenLib("table", luaopen_table);
		
		luaState["Start"]();
	}

	Script::~Script()
	{
	}
	
	void Script::run()
	{
		luaState["Update"]();
		
		if(bool(luaState["Done"]) == true)
		{
			luaState["Finish"]();
			deleteMe = true;
		}
	}
			
	bool Script::toDelete()
	{
		return deleteMe;
	}
}
