#include "Name.hpp"

#include "../Entity.hpp"

namespace swift
{
	Name::Name()
		:	name("")
	{
	}
	
	std::string Name::getType()
	{
		return "Name";
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
	
	/*template<>
	Name* Entity::get(std::string c)
	{
		if(c != "Name")
			return nullptr;
		
		if(this->has<Name>())
		{
			return static_cast<Name*>(components["Name"]);
		}
		else
			return nullptr;
	}*/
}
