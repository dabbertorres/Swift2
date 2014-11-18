#include "Movable.hpp"

#include "../Entity.hpp"

namespace swift
{
	Movable::Movable()
		:	moveVelocity(0),
			velocity(0, 0)
	{
	}
	
	std::string Movable::getType()
	{
		return "Movable";
	}
	
	std::map<std::string, std::string> Movable::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("moveVelocity", std::to_string(moveVelocity));
		variables.emplace("velocityX", std::to_string(velocity.x));
		variables.emplace("velocityY", std::to_string(velocity.y));
		
		return std::move(variables);
	}
	
	void Movable::unserialize(const std::map<std::string, std::string>& variables)
	{
		moveVelocity = std::stof(variables.at("moveVelocity"));
		velocity.x = std::stof(variables.at("velocityX"));
		velocity.y = std::stof(variables.at("velocityY"));
	}
}
