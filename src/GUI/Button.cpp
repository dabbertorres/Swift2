#include "Button.hpp"

const int BRIGHTEN = 20;
const int DARKEN = 40;

namespace sgui
{
	Button::Button(int x, int y, int width, int height) : Widget::Widget(x, y, width, height)
	{		
		rect.setPosition(sf::Vector2f(x, y));
		rect.setSize(sf::Vector2f(width, height));
		rect.setFillColor(color);
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(-2);
		
		text.setString(str);
		text.setColor(sf::Color::White);
		
		// resize text to fit within bounds
		text.setCharacterSize(text.getCharacterSize() * ((width - 3) / (text.getGlobalBounds().width - 3)));
		
		// set drawing origin of text to it's center
		text.setOrigin(	text.getGlobalBounds().left + text.getGlobalBounds().width / 2.0, 
						text.getGlobalBounds().top + text.getGlobalBounds().height / 2.0);
		
		// set position of text to the center of the button
		text.setPosition(x + (width / 2.0), y + (height / 2.0));
	}

	Button::~Button()
	{
	}
	
	void Button::run(int k = -1)
	{
		if(k != -1)
			return;
		func(true);
	}
	
	sf::FloatRect Button::getGlobalBounds() const
	{
		return rect.getGlobalBounds();
	}
	
	void Button::setFont(const sf::Font& f)
	{
		text.setFont(f);
	}
	
	void Button::setTextSize(unsigned ts)
	{
		text.setCharacterSize(ts);
	}
			
	void Button::setString(const std::string& s)
	{
		str = s;
	}
			
	void Button::setColor(const sf::Color& c)
	{
		color = c;
		rect.setFillColor(color);
	}
	
	void Button::setCall(const std::function<void(bool)>& f)
	{
		func = f;
	}
	
	void Button::clickPressFeedback()
	{
		rect.setFillColor(sf::Color(color.r - DARKEN < 0 ? color.r : color.r - DARKEN,
									color.g - DARKEN < 0 ? color.g : color.g - DARKEN,
									color.b - DARKEN < 0 ? color.b : color.b - DARKEN));	// darken the button,
																							// but check for going under 0
	}
	
	void Button::clickReleaseFeedback()
	{
		rect.setFillColor(color);	// return to normal
	}

	void Button::mousedOverFeedback()
	{
		rect.setFillColor(sf::Color(color.r + BRIGHTEN > 255 ? color.r : color.r + BRIGHTEN,
									color.g + BRIGHTEN > 255 ? color.g : color.g + BRIGHTEN,
									color.b + BRIGHTEN > 255 ? color.b : color.b + BRIGHTEN));	// brighten the button,
																								// but check for going over 255
	}
	
	void Button::mousedOffFeedback()
	{
		rect.setFillColor(color);	// return to normal
	}
	
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		//states.transform *= rect.getTransform();
		//states.transform *= text.getTransform();
		target.draw(rect, states);
		target.draw(text, states);
	}
}
