#include "Pathfinder.hpp"

#include "Physical.hpp"
#include "Movable.hpp"

namespace swift
{
	Pathfinder::Pathfinder(unsigned int id)
	:	Component(id),
		destination({0, 0}),
		needsPath(false)
	{}
	
	std::map<std::string, std::string> Pathfinder::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("destinationX", std::to_string(destination.x));
		variables.emplace("destinationY", std::to_string(destination.y));
		variables.emplace("needsPath", needsPath ? "true" : "false");
		
		return variables;
	}
	
	void Pathfinder::unserialize(const std::map<std::string, std::string>& variables)
	{
		destination = {std::stof(variables.at("destinationX")), std::stof(variables.at("destinationY"))};
		needsPath = variables.at("needsPath") == "true";
	}
}
