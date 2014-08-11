#include "Window.hpp"
#include <cassert>

namespace cstr
{
	Window::Window()
		:	activeWidget(nullptr),
			font(nullptr)
	{
	}

	Window::~Window()
	{
		for(auto w : widgets)
			delete w;
	}
	
	void Window::update(sf::Event& event)
	{
		switch(event.type)
		{
			case sf::Event::MouseMoved:
				activeWidget = nullptr;
				for(auto& w : widgets)
				{
					w->mouseMovedOff();
					if(w->contains({event.mouseMove.x, event.mouseMove.y}))
						activeWidget = w;
				}
				if(activeWidget)
					activeWidget->mouseMovedOn();
				break;
			case sf::Event::MouseButtonPressed:
				if(activeWidget)
					activeWidget->mousePressed();
				break;
			case sf::Event::MouseButtonReleased:
				if(activeWidget)
					activeWidget->mouseReleased();
				break;
			case sf::Event::TextEntered:
				if(activeWidget)
					if(event.text.unicode < 128)
						activeWidget->textEntered(static_cast<char>(event.text.unicode));
				break;
			default:
				break;
		}
	}
	
	void Window::setFont(sf::Font& font)
	{
		this->font = &font;
	}
	
	Button& Window::addButton(sf::IntRect rect, const sf::Texture& tex, const std::function<void()>& f)
	{
		unsigned oldSize = widgets.size();
		
		Button* b = new Button(rect, tex, f);
		
		if(font)
			b->setFont(*font);
		
		widgets.push_back(b);
		assert(widgets.size() > oldSize);
		
		return *b;
	}
	
	Label& Window::addLabel(const sf::Vector2i& pos, const std::string& str)
	{
		unsigned oldSize = widgets.size();
		
		Label* l = new Label(pos, str, *font);
		widgets.push_back(l);
		assert(widgets.size() > oldSize);
		
		return *l;
	}
	
	Toggle& Window::addToggle(sf::IntRect rect, const sf::Texture& off, const sf::Texture& on, bool s)
	{
		unsigned oldSize = widgets.size();
		
		Toggle* t = new Toggle(rect, off, on, s);
		widgets.push_back(t);
		assert(widgets.size() > oldSize);
		
		return *t;
	}
	
	TextBox& Window::addTextBox(sf::IntRect rect, const sf::Color& in, const sf::Color& out)
	{
		unsigned oldSize = widgets.size();
		
		TextBox* tb = new TextBox(rect, in, out, *font);
		widgets.push_back(tb);
		assert(widgets.size() > oldSize);
		
		return *tb;
	}
	
	Widget& Window::getWidget(unsigned i)
	{
		assert(i < widgets.size());
		return *widgets[i];
	}
	
	void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for(auto w : widgets)
		{
			target.draw(*w, states);
		}
	}
}
