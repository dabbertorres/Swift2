#include "Component.hpp"

namespace swift
{
	Component::Component(unsigned id)
		:	ID(id)
	{
	}

	Component::~Component()
	{
	}
	
	unsigned Component::getID() const
	{
		return ID;
	}
}
