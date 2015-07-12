#include "ScriptableSystem.hpp"

namespace swift
{
	void ScriptableSystem::update(float)
	{
		for(auto& c : components)
		{
			if(c.second.script)
			{
				c.second.script->update();
			}
		}
	}
	
	void ScriptableSystem::addImpl(const Scriptable& s)
	{
		s.script->start();
	}
	
	void ScriptableSystem::removeImpl(const Scriptable&)
	{
		
	}
}
