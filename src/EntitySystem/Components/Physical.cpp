#include "Physical.hpp"

#include "../Entity.hpp"

namespace swift
{
	Physical::Physical()
		:	position({0, 0}),
			size({0, 0}),
			collides(false)
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
		variables.emplace("sizeX", std::to_string(size.x));
		variables.emplace("sizeY", std::to_string(size.y));
		variables.emplace("collides", collides ? "true" : "false");
		
		return std::move(variables);
	}
	
	void Physical::unserialize(const std::map<std::string, std::string>& variables)
	{
		position.x = std::stoi(variables.at("positionX"));
		position.y = std::stoi(variables.at("positionY"));
		size.x = std::stoi(variables.at("sizeX"));
		size.y = std::stoi(variables.at("sizeY"));
		collides = variables.at("collides") == "true" ? true : false;
	}
	
	/*template<>
	Physical* Entity::get(std::string c)
	{
		if(c != "Physical")
			return nullptr;
		
		if(this->has<Physical>())
		{
			return static_cast<Physical*>(components["Physical"]);
		}
		else
			return nullptr;
	}*/
}
