#include "Label.hpp"

namespace cstr
{
	Label::Label(const std::string& str, const sf::Font& f)
		:	string(str)
	{
		text.setFont(f);
		text.setString(string);
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
	
	void Label::setString(const std::string& str)
	{
		string = str;
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
		text.setCharacterSize(text.getCharacterSize() * static_cast<float>(size.x / text.getGlobalBounds().width));
		text.setOrigin({text.getLocalBounds().left, text.getLocalBounds().top});
	}
	
	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text, states);
	}
}
