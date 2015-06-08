#include "ScriptSave.hpp"

namespace swift
{
	void ScriptSave::load(Script& s)
	{
		if(s.luaState["Load"])
		{
			lua_getglobal(s.luaState, "Load");
			
			for(auto& v : variables)
			{
				switch(v.first)
				{
					case LUA_TNUMBER:
						lua_pushnumber(s.luaState, std::stof(v.second));
						break;

					case LUA_TBOOLEAN:
						lua_pushboolean(s.luaState, v.second == "true" ? true : false);
						break;

					case LUA_TSTRING:
						lua_pushstring(s.luaState, v.second.c_str());
						break;
					
					default:
						lua_pushnil(s.luaState);
						break;
				}
			}
			
			lua_pcall(s.luaState, variables.size(), 0, 0);
		}
	}
	
	void ScriptSave::save(Script& s)
	{
		if(s.luaState["Save"])
		{
			// clear out our data and luaState's stack
			variables.clear();
			s.luaState.clean();
			
			// call save function
			s.luaState["Save"]();

			int totalRets = s.luaState.getTop();

			for(int i = 1; i <= totalRets; i++)
			{
				auto type = s.luaState[i].getType();

				switch(type)
				{
					case LUA_TNUMBER:
						variables.emplace_back(LUA_TNUMBER, std::to_string(static_cast<float>(s.luaState[i])));
						break;

					case LUA_TBOOLEAN:
						variables.emplace_back(LUA_TBOOLEAN, s.luaState[i] ? "true" : "false");
						break;

					case LUA_TSTRING:
					{
						std::string temp = s.luaState[i];
						variables.emplace_back(LUA_TSTRING, temp);
						break;
					}
					
					default:
						variables.emplace_back(LUA_TNIL, "nil");
						break;
				}
			}
		}
	}
	
	const std::string& ScriptSave::getName() const
	{
		return name;
	}
	
	ScriptSave::ScriptSave(Script& s)
	:	name(s.getFile())
	{
		save(s);
	}
	
	ScriptSave::ScriptSave(const std::string& n)
	:	name(n)
	{}
}
