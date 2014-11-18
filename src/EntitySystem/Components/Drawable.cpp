#include "Drawable.hpp"

#include "../Entity.hpp"

namespace swift
{
	std::string Drawable::getType()
	{
		return "Drawable";
	}
	
	std::map<std::string, std::string> Drawable::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("texture", texture);
		variables.emplace("scaleX", std::to_string(sprite.getScale().x));
		variables.emplace("scaleY", std::to_string(sprite.getScale().y));
		
		return std::move(variables);
	}
	
	void Drawable::unserialize(const std::map<std::string, std::string>& variables)
	{
		texture = variables.at("texture");
		sprite.setScale(std::stof(variables.at("scaleX")), std::stof(variables.at("scaleY")));
	}
}
