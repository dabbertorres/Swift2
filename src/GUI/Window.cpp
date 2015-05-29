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
	
	void Window::update(const sf::Event& event)
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
	
	void Window::clear()
	{
		for(unsigned i = 0; i < containers.size(); i++)
		{
			delete containers[i];
		}
		
		containers.clear();
	}
	
	void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for(auto& c : containers)
		{
			target.draw(*c, states);
		}
	}
}
