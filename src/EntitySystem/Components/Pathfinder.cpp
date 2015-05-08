#include "Pathfinder.hpp"

namespace swift
{
	Pathfinder::Pathfinder(unsigned int id, const Physical& p, Movable& m)
	:	Component(id),
		destination({0, 0}),
		needsPath(false),
		physical(p),
		movable(m)
	{}
	
	const Physical& Pathfinder::getPhysical() const
	{
		return physical;
	}
	
	Movable& Pathfinder::getMovable() const
	{
		return movable;
	}
	
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
