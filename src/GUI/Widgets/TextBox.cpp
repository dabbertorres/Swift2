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
		border.setOutlineColor( {128, 128, 128});
		border.setOutlineThickness(-BORDER_SIZE);
		border.setFillColor(sf::Color::Transparent);

		text.setFont(f);
		text.setString("|||");	// set a tall character to correctly set the origin
		text.setOrigin( {text.getLocalBounds().left, text.getLocalBounds().top});
		text.setCharacterSize(border.getGlobalBounds().height - 2 * BORDER_SIZE);
		text.setPosition(border.getGlobalBounds().left + BORDER_SIZE, border.getGlobalBounds().top + BORDER_SIZE);
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

					setDisplayedString();
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

					setDisplayedString();
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
		text.setPosition(pos.x + BORDER_SIZE, pos.y + BORDER_SIZE);
	}

	void TextBox::setSize(sf::Vector2u size)
	{
		border.setSize(static_cast<sf::Vector2f>(size));
		text.setCharacterSize(size.y - 2 * BORDER_SIZE);
		text.setOrigin( {text.getLocalBounds().left, text.getLocalBounds().top});
		text.setPosition(border.getGlobalBounds().left + BORDER_SIZE, border.getGlobalBounds().top + BORDER_SIZE);
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
		float maxWidth = border.getGlobalBounds().width - 2 * BORDER_SIZE;

		if(text.getGlobalBounds().width > maxWidth)
		{
			std::string beforeCursor = currentStr.substr(0, cursorPosition);
			std::string afterCursor = currentStr.substr(cursorPosition);

			text.setString('|');

			bool frontOfCursor = true;
			bool frontEmpty = false;
			bool backEmpty = false;
			int fronts = 0;
			int backs = 0;
			char newChar = '\0';
			sf::FloatRect newCharBounds = {0, 0, 0, 0};
			
			while(text.getGlobalBounds().width + newCharBounds.width < maxWidth && (!frontEmpty || !backEmpty))
			{
				if(frontOfCursor)
				{
					if(newChar != '\0')
						text.setString(newChar + text.getString());
					
					// calculate for after cursor
					if(!backEmpty)
					{
						newChar = afterCursor[fronts];
						fronts++;
						if(fronts + 1 > static_cast<int>(afterCursor.size()))
							backEmpty = true;
					}
					else
					{
						newChar = '\0';
					}
				}
				else
				{
					if(newChar != '\0')
						text.setString(text.getString() + newChar);
					
					// calculate for before cursor
					if(!frontEmpty)
					{
						newChar = beforeCursor[cursorPosition - 1 - backs];
						backs++;
						if(cursorPosition - 1 - backs - 1 < 0)
							frontEmpty = true;
					}
					else
					{
						newChar = '\0';
					}
				}
				
				frontOfCursor = !frontOfCursor;
				newCharBounds = text.getFont()->getGlyph(newChar, text.getCharacterSize(), false).bounds;
			}
		}
	}
}
