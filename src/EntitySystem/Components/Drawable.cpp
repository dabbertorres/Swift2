#include "Drawable.hpp"

#include "../Entity.hpp"

namespace swift
{
	void Drawable::setTexture(const sf::Texture& texture)
	{
		sprite.setTexture(texture, true);
	}
	
	void Drawable::setTextureRect(const sf::Texture& texture, sf::IntRect& rect)
	{
		sprite.setTexture(texture, true);
		sprite.setTextureRect(rect);
	}
	
	std::string Drawable::getType()
	{
		return "Drawable";
	}
	
	template<>
	Drawable* Entity::get(std::string c)
	{
		if(c != "Drawable")
			return nullptr;
		
		if(this->has<Drawable>())
		{
			return static_cast<Drawable*>(components["Drawable"]);
		}
		else
			return nullptr;
	}
}
