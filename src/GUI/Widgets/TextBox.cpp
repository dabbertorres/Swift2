#include "TextBox.hpp"

namespace cstr
{
	TextBox::TextBox(sf::Vector2u size, sf::Font& f, const std::string& d, const std::string& c)
		:	defaultStr(d),
		    currentStr(c),
		    selected(false),
		    border(static_cast<sf::Vector2f>(size))

	{
		text.setFont(f);
		text.setString("TTTTTTTTTTTTTT");	// set a tall character to correctly set the origin
		text.setOrigin({text.getLocalBounds().left, text.getLocalBounds().top});
		text.setString(c);
		text.setCharacterSize(border.getGlobalBounds().height - 4);

		border.setOutlineColor({128, 128, 128});
		border.setOutlineThickness(-2);
		border.setFillColor(sf::Color::Transparent);
	}

	TextBox::~TextBox()
	{
	}

	void TextBox::update(sf::Event& event)
	{
		switch(event.type)
		{
			case sf::Event::TextEntered:
				if(selected)
				{
					char c = event.text.unicode;
					// 8 = backspace, 13 = enter/return, 27 = escape, 127 = delete
					if(!(c == 8 || c == 13 || c == 27 || c == 127))
						currentStr += event.text.unicode;
					else if(c == 8)
					{
						if(currentStr.size() > 0)
							currentStr.erase(currentStr.size() - 1);
					}
					
					text.setString(currentStr);
					
					std::string temp = currentStr;
					while(text.getGlobalBounds().width > border.getGlobalBounds().width)
					{
						temp = temp.substr(1);
						text.setString(temp);
					}
				}
				break;
			case sf::Event::MouseMoved:
				if(border.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
					selected = true;
				else
					selected = false;
			default:
				break;
		}
	}

	sf::FloatRect TextBox::getGlobalBounds() const
	{
		return border.getGlobalBounds();
	}

	void TextBox::setPosition(sf::Vector2i pos)
	{
		border.setPosition(static_cast<sf::Vector2f>(pos));
		text.setPosition(pos.x + 2, pos.y - 1);
	}

	void TextBox::setSize(sf::Vector2u size)
	{
		border.setSize(static_cast<sf::Vector2f>(size));
		text.setCharacterSize(size.y - 4);
		text.setOrigin({text.getLocalBounds().left, text.getLocalBounds().top});
	}

	const std::string& TextBox::getString() const
	{
		return currentStr;
	}

	void TextBox::setTextColor(const sf::Color& tc)
	{
		text.setColor(tc);
	}

	void TextBox::setOutlineColor(const sf::Color& oc)
	{
		border.setOutlineColor(oc);
	}
	
	void TextBox::setBackgroundColor(const sf::Color& bc)
	{
		border.setFillColor(bc);
	}

	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(border, states);
		target.draw(text, states);
	}
}
