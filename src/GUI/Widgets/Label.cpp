#include "Label.hpp"

namespace cstr
{
	Label::Label(const std::string& str, const sf::Font& f, unsigned ts)
		:	string(str),
			textSize(ts)
	{
		text.setFont(f);
		text.setString(string);
		textSize == 0 ? text.setCharacterSize(100) : text.setCharacterSize(textSize);
		text.setOrigin({text.getLocalBounds().left, text.getLocalBounds().top});
	}

	Label::~Label()
	{
	}
	
	void Label::update(sf::Event& /*event*/)
	{
		// do nothing
	}

	sf::FloatRect Label::getGlobalBounds() const
	{
		return text.getGlobalBounds();
	}
	
	void Label::setString(const std::string& str, unsigned ts)
	{
		string = str;
		text.setString(string);
		
		if(ts != 0)
		{
			textSize = ts;
			text.setCharacterSize(textSize);
		}
		else
		{
			textSize = 0;
		}
		
	}
	
	const std::string& Label::getString() const
	{
		return string;
	}
	
	void Label::setPosition(sf::Vector2i pos)
	{
		text.setPosition(static_cast<sf::Vector2f>(pos));
	}
	
	void Label::setSize(sf::Vector2u size)
	{
		text.setCharacterSize(size.y);
		if(textSize == 0 && text.getLocalBounds().width > size.x)
			text.setCharacterSize(size.y * static_cast<float>(size.x) / text.getLocalBounds().width);
		else
			text.setCharacterSize(textSize);
		text.setOrigin({text.getLocalBounds().left, text.getLocalBounds().top});
	}
	
	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text, states);
	}
}
