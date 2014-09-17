#include "Physical.hpp"

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
}
