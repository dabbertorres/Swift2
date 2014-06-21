#include "Toggle.hpp"

const sf::Color COLOR_CHANGE = sf::Color(40, 40, 40, 0);

namespace cstr
{
	Toggle::Toggle(sf::IntRect rect, const sf::Texture& off, const sf::Texture& on, bool s)
		:	offTex(off), onTex(on), state(s)
	{
		sprite.setTexture(state ? onTex : offTex);
		sprite.setPosition(rect.left, rect.top);
		sprite.setScale(static_cast<float>(rect.width) / static_cast<float>(off.getSize().x), 
						static_cast<float>(rect.height) / static_cast<float>(off.getSize().y));
		
		color = {128, 128, 128};
		sprite.setColor(color);
	}

	Toggle::~Toggle()
	{
	}

	bool Toggle::getState() const
	{
		return state;
	}
	
	void Toggle::setState(bool s)
	{
		state = s;
		sprite.setTexture(state ? onTex : offTex);
	}
	
	sf::FloatRect Toggle::getGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}

	bool Toggle::contains(sf::Vector2i point)
	{
		return sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(point));
	}
	
	void Toggle::mousePressed()
	{
		sprite.setColor(color - COLOR_CHANGE);
	}
	
	void Toggle::mouseReleased()
	{
		sprite.setColor(color);
		state = !state;
		sprite.setTexture(state ? onTex : offTex);
	}
	
	void Toggle::mouseMovedOn()
	{
		sprite.setColor(color + COLOR_CHANGE);
	}
	
	void Toggle::mouseMovedOff()
	{
		sprite.setColor(color);
	}
	
	void Toggle::textEntered(char /*c*/)
	{
		// do nothing
	}

	void Toggle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}
}
