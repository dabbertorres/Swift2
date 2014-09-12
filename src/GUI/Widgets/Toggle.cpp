#include "Toggle.hpp"

namespace cstr
{
	const sf::Color COLOR_CHANGE = {40, 40, 40, 0};
	
	Toggle::Toggle(sf::Vector2u size, const sf::Texture& on, const sf::Texture& off, bool s, std::function<void(bool s)> c)
		:	baseColor({128, 128, 128}),
			onTex(on),
			offTex(off),
			callback(c),
			state(s)
	{
		sprite.setTexture(state ? onTex : offTex);
		sprite.setColor(baseColor);
		sprite.scale(size.x / sprite.getGlobalBounds().width, size.y / sprite.getGlobalBounds().height);
	}

	Toggle::~Toggle()
	{
	}
	
	bool Toggle::getState() const
	{
		return state;
	}

	void Toggle::update(sf::Event& event)
	{
		switch(event.type)
		{
			case sf::Event::MouseMoved:
				if(sprite.getGlobalBounds().contains({static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)}))
				{
					mouseOn = true;
					sprite.setColor(baseColor + COLOR_CHANGE);
				}
				else
				{
					mouseOn = false;
					sprite.setColor(baseColor);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if(mouseOn)
					sprite.setColor(baseColor - COLOR_CHANGE);
				break;
			case sf::Event::MouseButtonReleased:
				if(mouseOn)
				{
					state = !state;
					sprite.setTexture(state ? onTex : offTex);
					sprite.setColor(baseColor);
					callback(state);
				}
				break;
			default:
				break;
		}
	}
	
	sf::FloatRect Toggle::getGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}
	
	void Toggle::setPosition(sf::Vector2i pos)
	{
		sprite.setPosition(static_cast<sf::Vector2f>(pos));
	}
	
	void Toggle::setSize(sf::Vector2u size)
	{
		sprite.scale({size.x / sprite.getGlobalBounds().width, size.y / sprite.getGlobalBounds().height});
	}
	
	void Toggle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}
}
