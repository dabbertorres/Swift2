#include "Save.hpp"

#include <stdexcept>

namespace swift
{
	Save::Save(const std::string& n)
	:	name(n),
		lastWorld("")
	{
		if(name.back() != '/')
			name += '/';
		
		if(name.find("..") != std::string::npos || name.find("~") != std::string::npos)
		{
			throw std::invalid_argument("Not allowed to access files outside of save directory!");
		}
	}
	
	bool Save::isValid() const
	{
		return !name.empty();
	}
	
	const std::string& Save::getName() const
	{
		return name;
	}
	
	const std::string& Save::getLastWorld() const
	{
		return lastWorld;
	}
	
	void Save::setLastWorld(const std::string& worldName)
	{
		lastWorld = worldName;
	}
}
