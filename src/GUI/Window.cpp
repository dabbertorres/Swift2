#include "Window.hpp"

namespace cstr
{
	Window::Window()
		:	font(nullptr),
			textSize(0)
	{
	}

	Window::~Window()
	{
		for(auto& c : containers)
			delete c;
	}
	
	void Window::update(sf::Event& event)
	{
		for(auto& c : containers)
		{
			c->update(event);
		}
	}
	
	void Window::setTextSize(unsigned s)
	{
		textSize = s;
	}
	
	void Window::setFont(sf::Font& font)
	{
		this->font = &font;
	}
	
	void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for(auto& c : containers)
		{
			target.draw(*c, states);
		}
	}
}
