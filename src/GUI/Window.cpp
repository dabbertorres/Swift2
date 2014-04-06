#include "Window.hpp"

namespace sgui
{
	Window::Window(const sf::Window& w, const sf::Font& f, unsigned ts, bool a)
			:	window(w),
				font(f)
	{
		active = a;
		//org = o;
		//rows_cols = d;
		//organize();
		activeTextBox = nullptr;
		textSize = ts;
	}

	Window::~Window()
	{
	}

	void Window::update(sf::Event event)
	{
		if(active)
		{
			if(event.type == sf::Event::MouseMoved)
			{
				for(unsigned i = 0; i < children.size(); i++)
				{
					if(children[i]->isActive())
					{
						sf::FloatRect boundingBox = children[i]->getGlobalBounds();
						if(boundingBox.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
						{
							children[i]->mousedOver(true);
						}
						else
						{
							children[i]->mousedOver(false);
						}
					}
				}
			}

			if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				for(unsigned i = 0; i < children.size(); i++)
				{
					if(children[i]->isActive())
					{
						if(children[i]->isMouseOn())
						{
							children[i]->clickedOn(true);
							break;	// If we found the widget the mouse was on, it can't be elsewhere, so stop checking!
						}
					}
				}
			}

			if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				for(unsigned i = 0; i < children.size(); i++)
				{
					if(children[i]->isActive())
					{
						children[i]->clickedOn(false);
						if(children[i]->isMouseOn())
						{
							children[i]->run();
							break;	// If we found the widget the mouse was on, it can't be elsewhere, so stop checking!
						}
					}
				}
			}
			
			if(event.type == sf::Event::TextEntered)
			{
				if(activeTextBox != nullptr)
				{
					activeTextBox->run(event.text.unicode);
				}
			}
		}
	}
	
	void Window::addChild(Widget* c)
	{
		children.push_back(std::unique_ptr<Widget>(c));
		auto it = children.end();
		it--;
		it->get()->setFont(font);
		it->get()->setTextSize(textSize);
		//organize();
	}
	
	Widget& Window::getChild(unsigned c) const
	{
		return *children[c].get();
	}

	bool Window::toggle()
	{
		return active = !active;
	}

	bool Window::isActive() const
	{
		return active;
	}

	void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if(active)
		{
			for(unsigned i = 0; i < children.size(); i++)
			{
				if(children[i]->isActive())
					target.draw(*children[i], states);
			}
		}
	}

	// to be added in the future
	/*void Window::organize()
	{
		if(org == Custom)
			return;

		if(org == Horizontal)
		{
			for(unsigned i = 0; i < children.size(); i++)
			{
				children[i]->getGlobalBounds().width
			}
		}
		else
		{

		}
	}*/
}
