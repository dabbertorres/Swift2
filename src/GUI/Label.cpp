#include "Label.hpp"
#include <iostream>
namespace sgui
{
	Label::Label(int x, int y, int width, int height)
				: Widget::Widget(x, y, width, height)
	{
		text.setString(str);

		// resize text to fit within bounds
		text.setCharacterSize(text.getCharacterSize() * (width / text.getGlobalBounds().width));

		text.setPosition(x, y);
	}

	Label::~Label()
	{
	}
	
	// does nothing because labels don't run
	void Label::run(int k = -1) {}

	sf::FloatRect Label::getGlobalBounds() const
	{
		return text.getGlobalBounds();
	}
	
	void Label::setFont(const sf::Font& f)
	{
		text.setFont(f);
		std::cerr << text.getFont()->getInfo().family << '\n';
	}
	
	void Label::setTextSize(unsigned ts)
	{
		text.setCharacterSize(ts);
	}
			
	void Label::setString(const std::string& s)
	{
		str = s;
	}
			
	void Label::setColor(const sf::Color& c)
	{
		text.setColor(c);
	}
	
	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		//states.transform *= text.getTransform();
		target.draw(text, states);
	}
}
