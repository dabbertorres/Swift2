#include "BatchDrawable.hpp"

namespace swift
{
	std::string BatchDrawable::getType()
	{
		return "BatchDrawable";
	}
	
	std::map<std::string, std::string> BatchDrawable::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("texture", texture);
		variables.emplace("scaleX", std::to_string(sprite.getScale().x));
		variables.emplace("scaleY", std::to_string(sprite.getScale().y));
		variables.emplace("batch", batch);
		
		return std::move(variables);
	}
	
	void BatchDrawable::unserialize(const std::map<std::string, std::string>& variables)
	{
		initMember("texture", variables, texture, std::string("./data/textures/ship.png"));
		sf::Vector2f scale;
		initMember("scaleX", variables, scale.x, 0.f);
		initMember("scaleY", variables, scale.y, 0.f);
		sprite.setScale(scale);
		initMember("batch", variables, batch, std::string(""));
	}
}
