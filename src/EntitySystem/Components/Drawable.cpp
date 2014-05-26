#include "Drawable.hpp"

namespace swift
{	
	Drawable::Drawable(const sf::Texture& texture)
		:	Component(1234)
	{
		sprite.setTexture(texture);
	}

	Drawable::~Drawable()
	{
	}
	
	const sf::Sprite& Drawable::getSprite() const
	{
		return sprite;
	}
	
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}
}
