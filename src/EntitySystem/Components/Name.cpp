#include "Name.hpp"

namespace swift
{
	Name::Name(unsigned int id)
	:	Component(id),
		name("")
	{
	}
	
	std::map<std::string, std::string> Name::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("name", name);
		
		return std::move(variables);
	}
	
	void Name::unserialize(const std::map<std::string, std::string>& variables)
	{
		name = variables.at("name");
	}
}
