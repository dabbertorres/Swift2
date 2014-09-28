#include "Movable.hpp"

#include "../Entity.hpp"

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
	
	/*template<>
	Movable* Entity::get(std::string c)
	{
		if(c != "Movable")
			return nullptr;
		
		if(this->has<Movable>())
		{
			return static_cast<Movable*>(components["Movable"]);
		}
		else
			return nullptr;
	}*/
}
