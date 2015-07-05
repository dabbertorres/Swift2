#include "Movable.hpp"

#include "Physical.hpp"

namespace swift
{
	Movable::Movable(unsigned int id)
	:	Component(id),
		moveVelocity(0),
		velocity(0, 0)
	{}
	
	std::map<std::string, std::string> Movable::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("moveVelocity", std::to_string(moveVelocity));
		variables.emplace("velocityX", std::to_string(velocity.x));
		variables.emplace("velocityY", std::to_string(velocity.y));
		
		return variables;
	}
	
	void Movable::unserialize(const std::map<std::string, std::string>& variables)
	{
		moveVelocity = std::stof(variables.at("moveVelocity"));
		velocity = {std::stof(variables.at("velocityX")), std::stof(variables.at("velocityY"))};
	}
}
