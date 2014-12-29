#include "Controllable.hpp"

namespace swift
{
	Controllable::Controllable()
	:	moveLeft(false),
		moveRight(false),
		moveUp(false),
		moveDown(false)
	{}
	
	std::string Controllable::getType()
	{
		return "Controllable";
	}

	std::map<std::string,std::string> Controllable::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("moveLeft", moveLeft ? "true" : "false");
		variables.emplace("moveRight", moveRight ? "true" : "false");
		variables.emplace("moveUp", moveUp ? "true" : "false");
		variables.emplace("moveDown", moveDown ? "true" : "false");
		
		return std::move(variables);
	}
	
	void Controllable::unserialize(const std::map<std::string, std::string>& variables)
	{
		initMember("moveLeft", variables, moveLeft, false);
		initMember("moveRight", variables, moveRight, false);
		initMember("moveUp", variables, moveUp, false);
		initMember("moveDown", variables, moveDown, false);
	}
}
