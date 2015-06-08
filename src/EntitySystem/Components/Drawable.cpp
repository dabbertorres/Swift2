#include "Drawable.hpp"

#include "Physical.hpp"

namespace swift
{
	Drawable::Drawable(unsigned int id, const Physical& p)
	:	Component(id),
		physical(p)
	{}
	
	Drawable::Drawable(const Drawable& other)
	:	Component(other.ID()),
		sprite(other.sprite),
		texture(other.texture),
		physical(other.physical)
	{}
			
	Drawable& Drawable::operator=(Drawable&& other)
	{
		sprite = other.sprite;
		texture = other.texture;
		const_cast<Physical&>(physical) = other.physical;
		
		return *this;
	}
	
	const Physical& Drawable::getPhysical() const
	{
		return physical;
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
