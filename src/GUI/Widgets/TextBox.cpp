#include "TextBox.hpp"

namespace cstr
{
	const int BORDER_SIZE = 2;
	
	TextBox::TextBox(sf::Vector2u size, sf::Font& f, const std::string& d)
		:	currentStr(d),
			cursorPosition(currentStr.size()),
		    selected(false),
		    border(static_cast<sf::Vector2f>(size))

	{
		border.setOutlineColor({128, 128, 128});
		border.setOutlineThickness(-BORDER_SIZE);
		border.setFillColor(sf::Color::Transparent);
		
		text.setFont(f);
		text.setString("TTTTTTTTTTTTTT");	// set a tall character to correctly set the origin
		text.setOrigin({text.getLocalBounds().left, text.getLocalBounds().top});
		text.setCharacterSize(border.getGlobalBounds().height - 2 * BORDER_SIZE);
		text.setPosition(border.getGlobalBounds().left + BORDER_SIZE, border.getGlobalBounds().top);
		text.setString(currentStr + '|');
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
					{
						currentStr.insert(cursorPosition, 1, static_cast<char>(event.text.unicode));
						cursorPosition++;
					}
					else if(c == 8)
					{
						if(cursorPosition > 0)
						{
							currentStr.erase(cursorPosition - 1, 1);
							cursorPosition--;
						}
					}
					else if(c == 127)
					{
						if(cursorPosition < static_cast<int>(currentStr.size()))
						{
							currentStr.erase(cursorPosition, 1);
						}
					}
					
					text.setString(currentStr.substr(0, cursorPosition) + '|' + currentStr.substr(cursorPosition));
					
					//setDisplayedString();
				}
				break;
			case sf::Event::KeyPressed:
				if(selected)
				{
					switch(event.key.code)
					{
						case sf::Keyboard::Right:
							cursorPosition++;
							break;
						case sf::Keyboard::Left:
							cursorPosition--;
							break;
						case sf::Keyboard::Up:
							cursorPosition = currentStr.size();
							break;
						case sf::Keyboard::Down:
							cursorPosition = 0;
							break;
						default:
							break;
					}
					
					if(cursorPosition < 0)
						cursorPosition = 0;
					else if(cursorPosition > static_cast<int>(currentStr.size()))
						cursorPosition = currentStr.size();
						
					text.setString(currentStr.substr(0, cursorPosition) + '|' + currentStr.substr(cursorPosition));
					
					//setDisplayedString();
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
		text.setPosition(pos.x + BORDER_SIZE, pos.y);
	}

	void TextBox::setSize(sf::Vector2u size)
	{
		border.setSize(static_cast<sf::Vector2f>(size));
		text.setCharacterSize(size.y - 2 * BORDER_SIZE);
		text.setOrigin({text.getLocalBounds().left, text.getLocalBounds().top});
		text.setPosition(border.getGlobalBounds().left + BORDER_SIZE, border.getGlobalBounds().top);
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
	
	void TextBox::setDisplayedString()
	{
		int rightTimes = 0;
		while(text.findCharacterPos(currentStr.size() - rightTimes).x >= border.getGlobalBounds().left + border.getGlobalBounds().width && text.getString().find('|') != text.getString().getSize() - 1)
		{
			text.setString(currentStr.substr(0, cursorPosition) + '|' + currentStr.substr(cursorPosition, currentStr.size() - rightTimes - 1));
			rightTimes++;
		}
		
		int leftTimes = 0;
		while(text.findCharacterPos(currentStr.size() - leftTimes).x >= border.getGlobalBounds().left + border.getGlobalBounds().width && text.getString().find('|') != 0)
		{
			text.setString(currentStr.substr(leftTimes + 1, cursorPosition) + '|' + currentStr.substr(cursorPosition));
			leftTimes++;
		}
	}
}
