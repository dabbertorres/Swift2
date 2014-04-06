#include "Widget.hpp"

namespace sgui
{
	Widget::Widget(int x, int y, int width, int height)
	{
		mouseOn = false;
		clicked = false;
		active = true;
	}

	Widget::~Widget()
	{

	}

	void Widget::mousedOver(bool m)
	{
		// Had to use an if statement because I cannot have a "do nothing" with the conditional operator
		if(m)
		{
			if(!clicked)
				mousedOverFeedback();
		}
		else
			mousedOffFeedback();

		mouseOn = m;
	}

	void Widget::clickedOn(bool c)
	{
		c ? clickPressFeedback() : clickReleaseFeedback();
		clicked = c;
	}

	void Widget::setActive(bool a)
	{
		active = a;
	}

	bool Widget::isMouseOn() const
	{
		return mouseOn;
	}

	bool Widget::isClicked() const
	{
		return clicked;
	}

	bool Widget::isActive() const
	{
		return active;
	}

	void Widget::setFont(const sf::Font& f)
	{
		(void)f;
	}
	
	void Widget::setTextSize(unsigned ts)
	{
		(void)ts;
	}

	void Widget::setString(const std::string& s)
	{
		(void)s;
	}

	void Widget::setColor(const sf::Color& c)
	{
		(void)c;
	}

	void Widget::setCall(const std::function<void(bool)>& f)
	{
		(void)f;
	}
	
	void Widget::clickPressFeedback() {}
	
	void Widget::clickReleaseFeedback() {}

	void Widget::mousedOverFeedback() {}
	
	void Widget::mousedOffFeedback() {}
}
