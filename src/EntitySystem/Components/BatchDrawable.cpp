#include "BatchDrawable.hpp"

#include "Physical.hpp"

namespace swift
{
	BatchDrawable::BatchDrawable(unsigned int id)
	:	Component(id)
	{}
	
	std::map<std::string, std::string> BatchDrawable::serialize() const
	{
		std::map<std::string, std::string> variables;
		
		variables.emplace("texture", texture);
		variables.emplace("scaleX", std::to_string(sprite.getScale().x));
		variables.emplace("scaleY", std::to_string(sprite.getScale().y));
		variables.emplace("batch", batch);
		
		return variables;
	}
	
	void BatchDrawable::unserialize(const std::map<std::string, std::string>& variables)
	{
		texture = variables.at("texture");
		sprite.setScale({std::stof(variables.at("scaleX")), std::stof(variables.at("scaleY"))});
		batch = variables.at("batch");
	}
}
