#include "Scriptable.hpp"

namespace swift
{
	Scriptable::Scriptable(unsigned int id)
	:	Component(id)
	{}
	
	Scriptable::Scriptable(const Scriptable& other)
	:	Component(other.ID()),
		script(std::make_unique<Script>())
	{
		script->loadFromFile(other.script->getFile());
	}
	
	Scriptable& Scriptable::operator=(const Scriptable& other)
	{
		script = std::make_unique<Script>();
		script->loadFromFile(other.script->getFile());
		
		return *this;
	}

	std::map<std::string, std::string> Scriptable::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("file", script->getFile());
		
		return variables;
	}

	void Scriptable::unserialize(const std::map<std::string, std::string>& variables)
	{
		script = std::make_unique<Script>();
		script->loadFromFile(variables.at("file"));
	}
}
