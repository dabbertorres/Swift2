#include "Label.hpp"

namespace cstr
{
	Label::Label(const sf::Vector2f& pos, const std::string& str, const sf::Font& font)
	{
		text.setFont(font);
		text.setString(str);
		position = pos;
		text.setPosition(position);
	}

	Label::~Label()
	{
		
	}
	
	void Label::setFont(const sf::Font& font)
	{
		text.setFont(font);
		text.setPosition(position);
	}
	
	void Label::setText(const std::string& str)
	{
		text.setString(str);
		text.setPosition(position);
	}
	
	void Label::setTextColor(const sf::Color& tc)
	{
		text.setColor(tc);
	}
	
	void Label::setCharacterSize(unsigned size)
	{
		text.setCharacterSize(size);
	}
	
	sf::FloatRect Label::getGlobalBounds() const
	{
		return text.getGlobalBounds();
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
