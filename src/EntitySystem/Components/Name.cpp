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
