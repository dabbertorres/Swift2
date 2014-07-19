#include "TextBox.hpp"

namespace cstr
{
	TextBox::TextBox(const sf::IntRect& ir, const sf::Color& in, const sf::Color& out, const sf::Font& f)
	{
		rect.setPosition(ir.left, ir.top);
		rect.setSize({static_cast<float>(ir.width), static_cast<float>(ir.height)});
		rect.setFillColor(in);
		rect.setOutlineColor(out);
		rect.setOutlineThickness(-2);
		text.setFont(f);
		text.setPosition(rect.getPosition().x + 5, rect.getPosition().y + 5);
	}

	TextBox::~TextBox()
	{
	}
	
	void TextBox::setFont(const sf::Font& font)
	{
		text.setFont(font);
	}
	
	void TextBox::setTextColor(const sf::Color& tc)
	{
		text.setColor(tc);
	}
	
	void TextBox::setCharacterSize(unsigned size)
	{
		text.setCharacterSize(size);
	}
	
	const std::string& TextBox::getString() const
	{
		return string;
	}
	
	sf::FloatRect TextBox::getGlobalBounds() const
	{
		return rect.getGlobalBounds();
	}
	
	bool TextBox::contains(sf::Vector2i point)
	{
		return rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(point));
	}
	
	void TextBox::mousePressed()
	{
		
	}
	
	void TextBox::mouseReleased()
	{
		
	}
	
	void TextBox::mouseMovedOn()
	{
		
	}
	
	void TextBox::mouseMovedOff()
	{
		
	}
	
	void TextBox::textEntered(char c)
	{
		switch(c)
		{
			case '\b':
				string.erase(string.size() - 1, 1);
				break;
			default:
				string += c;
				break;
		}
		
		text.setString(string);
	}
	
	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rect, states);
		target.draw(text, states);
	}
}
