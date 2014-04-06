#include "Toggle.hpp"

const int BRIGHTEN = 20;
const int DARKEN = 40;

namespace sgui
{
	Toggle::Toggle(int x, int y, int width, int height)
			: Widget(x, y, width, height)
	{
		state = false;
		
		outline.setPosition(sf::Vector2f(x, y));
		outline.setSize(sf::Vector2f(width, height));
		outline.setFillColor(sf::Color::Transparent);
		outline.setOutlineColor(color);
		outline.setOutlineThickness(-2);
		
		checked.setPosition(sf::Vector2f(x + 5, y + 5));
		checked.setSize(sf::Vector2f(width - 10, height - 10));
		checked.setFillColor(state ? color : sf::Color::Transparent);
	}

	Toggle::~Toggle()
	{
	}
	
	void Toggle::setState(bool s)
	{
		state = s;
	}
	
	void Toggle::run(int k = -1)
	{
		if(k != -1)
			return;
		state = !state;
		checked.setFillColor(state ? color : sf::Color::Transparent);
		func(state);
	}

	sf::FloatRect Toggle::getGlobalBounds() const
	{
		return outline.getGlobalBounds();
	}
			
	void Toggle::setColor(const sf::Color& c)
	{
		color = c;
	}
	
	void Toggle::setCall(const std::function<void(bool)>& f)
	{
		func = f;
	}

	void Toggle::clickPressFeedback()
	{
		checked.setFillColor(sf::Color(color.r, color.g, color.b, color.a - 3 * DARKEN));	// fade the toggle
	}
	
	void Toggle::clickReleaseFeedback()
	{
		checked.setFillColor(state ? color : sf::Color::Transparent);	// return to normal
	}

	void Toggle::mousedOverFeedback()
	{
		checked.setFillColor(sf::Color(color.r, color.g, color.b, color.a - DARKEN));	// fade the toggle
	}
	
	void Toggle::mousedOffFeedback()
	{
		checked.setFillColor(state ? color : sf::Color::Transparent);	// return to normal	
	}
	
	void Toggle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(outline, states);
		target.draw(checked, states);
	}
}
