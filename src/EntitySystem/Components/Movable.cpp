#include "Movable.hpp"

namespace swift
{
	Movable::Movable()
		:	moveVelocity(0),
			velocity(0, 0)
	{
	}
	
	std::string Movable::getType()
	{
		return "Movable";
	}
}
