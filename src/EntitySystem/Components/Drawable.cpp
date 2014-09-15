#include "Drawable.hpp"

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
}
