#include "Physical.hpp"

#include "../Entity.hpp"

namespace swift
{
	Physical::Physical()
		:	position({0, 0}),
			previousPosition({0, 0}),
			size({0, 0})
	{
		
	}
	
	std::string Physical::getType()
	{
		return "Physical";
	}
	
	template<>
	Physical* Entity::get(std::string c)
	{
		if(c != "Physical")
			return nullptr;
		
		if(this->has<Physical>())
		{
			return static_cast<Physical*>(components["Physical"]);
		}
		else
			return nullptr;
	}
}
