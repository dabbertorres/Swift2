#include "Scriptable.hpp"

namespace swift
{
	Scriptable::Scriptable(unsigned int id)
	:	Component(id)
	{
	}

	std::map<std::string, std::string> Scriptable::serialize() const
	{
	}

	void Scriptable::unserialize(const std::map<std::string, std::string>& variables)
	{
	}
}
