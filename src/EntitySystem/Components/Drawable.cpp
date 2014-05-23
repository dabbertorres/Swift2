#include "Drawable.hpp"

namespace swift
{
	Drawable::Drawable(const sf::Texture& texture)
	{
		sprite.setTexture(texture);
	}

	Drawable::~Drawable()
	{
	}
	
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}
}
