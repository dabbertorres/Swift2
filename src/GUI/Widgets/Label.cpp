#include "Label.hpp"

namespace cstr
{
	Label::Label(const sf::Vector2f& pos, const std::string& str, const sf::Font& font)
	{
		text.setFont(font);
		text.setString(str);
		text.setOrigin(text.getGlobalBounds().left + text.getGlobalBounds().width / 2, text.getGlobalBounds().top + text.getGlobalBounds().height / 2);
		position = pos;
		text.setPosition(position);
	}

	Label::~Label()
	{
		
	}
	
	void Label::setFont(const sf::Font& font)
	{
		text.setFont(font);
		text.setOrigin(text.getGlobalBounds().left + text.getGlobalBounds().width / 2, text.getGlobalBounds().top + text.getGlobalBounds().height / 2);
		text.setPosition(position);
	}
	
	void Label::setText(const std::string& str)
	{
		text.setString(str);
		text.setOrigin(text.getGlobalBounds().left + text.getGlobalBounds().width / 2, text.getGlobalBounds().top + text.getGlobalBounds().height / 2);
		text.setPosition(position);
	}
	
	void Label::setTextColor(const sf::Color& tc)
	{
		text.setColor(tc);
	}
	
	bool Label::contains(sf::Vector2i /*point*/)
	{
		return false;
	}
	
	void Label::mousePressed()
	{
		
	}
	
	void Label::mouseReleased()
	{
		
	}
	
	void Label::mouseMovedOn()
	{
		
	}
	
	void Label::mouseMovedOff()
	{
		
	}
	
	void Label::textEntered(char /*c*/)
	{
		
	}
			
	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text, states);
	}
}