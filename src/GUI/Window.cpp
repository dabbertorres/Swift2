#include "Window.hpp"
#include <iostream>
namespace cstr
{
	Window::Window()
		:	activeWidget(nullptr)
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
				for(auto w : widgets)
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
	
	Button& Window::addButton(sf::IntRect rect, const sf::Texture& tex, const std::function<void()>& f)
	{
		Button* button = new Button(rect, tex, f);
		widgets.push_back(std::move(button));
		return *button;
	}
	
	Label& Window::addLabel(const sf::Vector2f& pos, const std::string& str, const sf::Font& font)
	{
		Label* label = new Label(pos, str, font);
		widgets.push_back(std::move(label));
		return *label;
	}
	
	Toggle& Window::addToggle(sf::IntRect rect, const sf::Texture& off, const sf::Texture& on, bool s)
	{
		Toggle* toggle = new Toggle(rect, off, on, s);
		widgets.push_back(std::move(toggle));
		return *toggle;
	}
	
	void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for(auto w : widgets)
		{
			target.draw(*w, states);
		}
	}
}
