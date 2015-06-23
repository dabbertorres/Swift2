#include "Controllable.hpp"

#include "Movable.hpp"

namespace swift
{
	Controllable::Controllable(unsigned int id)
	:	Component(id),
		moveLeft(false),
		moveRight(false),
		moveUp(false),
		moveDown(false)
	{}

	std::map<std::string,std::string> Controllable::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("moveLeft", moveLeft ? "true" : "false");
		variables.emplace("moveRight", moveRight ? "true" : "false");
		variables.emplace("moveUp", moveUp ? "true" : "false");
		variables.emplace("moveDown", moveDown ? "true" : "false");
		
		return variables;
	}
	
	void Controllable::unserialize(const std::map<std::string, std::string>& variables)
	{
		moveLeft = variables.at("moveLeft") == "true";
		moveRight = variables.at("moveRight") == "true";
		moveUp = variables.at("moveUp") == "true";
		moveDown = variables.at("moveDown") == "true";
	}
}
