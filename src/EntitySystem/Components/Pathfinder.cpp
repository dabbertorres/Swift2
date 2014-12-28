#include "Pathfinder.hpp"

namespace swift
{
	std::string Pathfinder::getType()
	{
		return "Pathfinder";
	}
	
	std::map<std::string, std::string> Pathfinder::serialize() const
	{
		return std::map<std::string, std::string>();
	}
	
	void Pathfinder::unserialize(const std::map<std::string, std::string>&)
	{
		
	}
}
