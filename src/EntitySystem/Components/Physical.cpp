#include "Physical.hpp"

#include "../Entity.hpp"

namespace swift
{
	Physical::Physical()
	:	position({0, 0}),
		zIndex(1),
		size({0, 0}),
		collides(false),
		angle(0)
	{
		
	}
	
	std::string Physical::getType()
	{
		return "Physical";
	}
	
	std::map<std::string, std::string> Physical::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("positionX", std::to_string(position.x));
		variables.emplace("positionY", std::to_string(position.y));
		variables.emplace("zIndex", std::to_string(zIndex));
		variables.emplace("sizeX", std::to_string(size.x));
		variables.emplace("sizeY", std::to_string(size.y));
		variables.emplace("collides", collides ? "true" : "false");
		variables.emplace("angle", std::to_string(angle));
		
		return std::move(variables);
	}
	
	void Physical::unserialize(const std::map<std::string, std::string>& variables)
	{
		initMember("positionX", variables, position.x, 0.f);
		initMember("positionY", variables, position.y, 0.f);
		initMember("zIndex", variables, zIndex, 0u);
		initMember("sizeX", variables, size.x, 0u);
		initMember("sizeY", variables, size.y, 0u);
		initMember("collides", variables, collides, false);
		initMember("angle", variables, angle, 0.f);
	}
}
