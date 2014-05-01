#include "Script.hpp"

namespace swift
{
	Script::Script()
	{
		deleteMe = false;
		
		// We don't want to give the scripts access to os commands or file writing abilities
		luaState.OpenLib("base", luaopen_base);
		luaState.OpenLib("math", luaopen_math);
		luaState.OpenLib("string", luaopen_string);
		luaState.OpenLib("table", luaopen_table);
	}

	Script::~Script()
	{
	}

	bool Script::loadFromFile(const std::string& file)
	{
		bool r = luaState.Load(file);	// r will be false if errors, true otherwise

		luaState["Start"]();
		return r;
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
