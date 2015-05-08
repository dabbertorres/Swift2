#include "Drawable.hpp"

namespace swift
{
	Drawable::Drawable(unsigned int id, const Physical& p)
	:	Component(id),
		physical(p)
	{}
	
	const Physical& Drawable::getPhysical() const
	{
		return physical;
	}
			
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
		initMember("texture", variables, texture, std::string("./data/textures/ship.png"));
		sf::Vector2f scale;
		initMember("scaleX", variables, scale.x, 0.f);
		initMember("scaleY", variables, scale.y, 0.f);
		sprite.setScale(scale);
	}
}
