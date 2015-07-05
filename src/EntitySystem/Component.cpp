#include "Component.hpp"

namespace swift
{
	Component::Component(unsigned int i)
	:	id(i)
	{}
	
	unsigned int Component::ID() const
	{
		return id;
	}
	
	constexpr std::pair<const char*, Component::Type> Component::TypeStrings[];
}
