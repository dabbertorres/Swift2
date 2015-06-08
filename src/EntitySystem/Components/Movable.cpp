#include "Movable.hpp"

#include "Physical.hpp"

namespace swift
{
	Movable::Movable(unsigned int id, Physical& p)
	:	Component(id),
		moveVelocity(0),
		velocity(0, 0),
		physical(p)
	{}
	
	Movable::Movable(const Movable& other)
	:	Component(other.ID()),
		moveVelocity(other.moveVelocity),
		velocity(other.velocity),
		physical(other.physical)
	{}
	
	Movable& Movable::operator=(const Movable& other)
	{
		moveVelocity = other.moveVelocity;
		velocity = other.velocity;
		physical = other.physical;
		
		return *this;
	}
	
	Movable& Movable::operator=(Movable&& other)
	{
		moveVelocity = other.moveVelocity;
		velocity = other.velocity;
		physical = other.physical;
		
		return *this;
	}
	
	Physical& Movable::getPhysical() const
	{
		return physical;
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
		velocity = {std::stof(variables.at("velocityX")), std::stof(variables.at("velocityY"))};
	}
}
