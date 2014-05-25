#include "Button.hpp"

const sf::Color COLOR_CHANGE = sf::Color(40, 40, 40, 0);

namespace cstr
{
	Button::Button(sf::IntRect rect, const sf::Texture& tex, const std::function<void()>& f)
		:	function(f)
	{
		sprite.setTexture(tex);
		sprite.setPosition(rect.left, rect.top);
		sprite.setScale(rect.width / static_cast<float>(tex.getSize().x), rect.height / static_cast<float>(tex.getSize().y));
		color = sf::Color(128, 128, 128);
		sprite.setColor(color);
		
		text.setOrigin(text.getGlobalBounds().left + text.getGlobalBounds().width / 2, text.getGlobalBounds().top + text.getGlobalBounds().height / 2);
		text.setPosition(	sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2,
							sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2);
	}

	Button::~Button()
	{
	}
	
	void Button::setFont(const sf::Font& font)
	{
		text.setFont(font);
		
		shrinkTextToFit();
			
		text.setOrigin(text.getGlobalBounds().left + text.getGlobalBounds().width / 2, text.getGlobalBounds().top + text.getGlobalBounds().height / 2);
		text.setPosition(	sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2,
							sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2);
	}
	
	void Button::setText(const std::string& str)
	{
		text.setString(str);
		
		shrinkTextToFit();
			
		text.setOrigin(text.getGlobalBounds().left + text.getGlobalBounds().width / 2, text.getGlobalBounds().top + text.getGlobalBounds().height / 2);
		text.setPosition(	sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2,
							sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2);
	}
	
	void Button::setTextColor(const sf::Color& tc)
	{
		text.setColor(tc);
	}
	
	void Button::setColor(const sf::Color& c)
	{
		color = c;
		sprite.setColor(color);
	}
	
	sf::Vector2f Button::getPosition() const
	{
		return sprite.getPosition();
	}
	
	bool Button::contains(sf::Vector2i point)
	{
		return sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(point));
	}
	
	void Button::mousePressed()
	{
		sprite.setColor(color - COLOR_CHANGE);
	}
	
	void Button::mouseReleased()
	{
		sprite.setColor(color);
		function();
	}
	
	void Button::mouseMovedOn()
	{
		sprite.setColor(color + COLOR_CHANGE);
	}
	
	void Button::mouseMovedOff()
	{
		sprite.setColor(color);
	}
	
	void Button::textEntered(char c)
	{
		// do nothing
	}
	
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
		target.draw(text, states);
	}
	
	void Button::shrinkTextToFit()
	{
		while(text.getGlobalBounds().width >= sprite.getGlobalBounds().width)
			text.setCharacterSize(text.getCharacterSize() - 1);
	}
}
