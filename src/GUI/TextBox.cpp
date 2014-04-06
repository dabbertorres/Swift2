#include "TextBox.hpp"

namespace sgui
{
	TextBox::TextBox(int x, int y, int width, int height)
		: Widget(x, y, width, height)
	{
		box.setPosition(x, y);
		box.setSize(sf::Vector2f(width, height));
		box.setFillColor(sf::Color::Transparent);
		box.setOutlineThickness(-2);
		box.setOutlineColor(sf::Color::Black);

		text.setString(str);
		text.setPosition(x + 2, y + 2);
		text.setColor(sf::Color(200, 200, 200));

		receiveText = false;

		// resize text to fit within bounds
		//text.setCharacterSize(text.getCharacterSize() * (width / text.getGlobalBounds().width));
	}

	TextBox::~TextBox()
	{
	}

	void TextBox::parse(const sf::Event& e)
	{

	}

	void TextBox::run(int k)
	{
		//if(!receiveText)
		//	return;
		if(k == '\b')
			str.erase(str.size() - 1, 1);
		else if(k == '\n' || k == '\r')
		{}
		else if(0 < k && k < 128)
			str += static_cast<char>(k);
	}
	
	sf::FloatRect TextBox::getGlobalBounds() const
	{
		return box.getGlobalBounds();
	}

	void TextBox::setFont(const sf::Font& f)
	{
		text.setFont(f);
	}

	void TextBox::setString(const std::string& s)
	{
		str = s;
	}

	const std::string& TextBox::getString() const
	{
		return str;
	}

	void TextBox::clickPressFeedback()
	{
		receiveText = true;
	}

	void TextBox::clickReleaseFeedback()
	{

	}

	void TextBox::mousedOverFeedback()
	{

	}

	void TextBox::mousedOffFeedback()
	{

	}

	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		//states.transform *= box.getTransform();
		//states.transform *= text.getTransform();
		target.draw(box, states);
		target.draw(text, states);
	}
}
