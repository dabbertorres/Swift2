#include "Physical.hpp"

namespace swift
{
	Physical::Physical(unsigned int id)
	:	Component(id),
		position({0, 0}),
		zIndex(1),
		size({0, 0}),
		collides(false),
		angle(0)
	{}
	
	Physical::Physical(const Physical& other)
	:	Component(other.ID()),
		position(other.position),
		zIndex(other.zIndex),
		size(other.size),
		collides(other.collides),
		angle(other.angle)
	{}
	
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
		position = {std::stof(variables.at("positionX")), std::stof(variables.at("positionY"))};
		zIndex = std::stoi(variables.at("zIndex"));
		size = {static_cast<unsigned int>(std::stoul(variables.at("sizeX"))), static_cast<unsigned int>(std::stoul(variables.at("sizeY")))};
		collides = variables.at("collides") == "true";
		angle = std::stof(variables.at("angle"));
	}
}
