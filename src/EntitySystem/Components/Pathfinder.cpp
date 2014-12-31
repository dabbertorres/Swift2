#include "Pathfinder.hpp"

namespace swift
{
	Pathfinder::Pathfinder()
	:	destination({0, 0}),
		needsPath(false)
	{}
	
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
