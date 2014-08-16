#include "Label.hpp"

namespace cstr
{
	Label::Label()
	{
		position = {0, 0};
		text.setPosition(position);
	}
	
	Label::Label(const sf::Vector2i& pos, const std::string& str, const sf::Font& font)
	{
		text.setFont(font);
		text.setString(str);
		position = {static_cast<float>(pos.x), static_cast<float>(pos.y)};
		text.setPosition(position);
	}

	Label::~Label()
	{
		
	}
	
	void Label::setFont(const sf::Font& font)
	{
		text.setFont(font);
	}
	
	void Label::setText(const std::string& str)
	{
		text.setString(str);
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
