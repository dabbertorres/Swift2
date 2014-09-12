#include "Row.hpp"
#include <iostream>
namespace cstr
{
	Row::Row(sf::IntRect r, bool s)
		:	Container(r, s)
	{
	}
	
	Row::Row(sf::Vector2i size, bool s)
		:	Container(size, s)
	{
	}

	Row::~Row()
	{
	}

	void Row::update(sf::Event& event)
	{
		if(isScrollable())
		{
			if(event.type == sf::Event::MouseMoved)
			{
				if(rect.contains({event.mouseMove.x, event.mouseMove.y}))
					mouseOn = true;
				else
					mouseOn = false;
			}
			else if(mouseOn && event.type == sf::Event::MouseWheelMoved)
			{
				scroll(event.mouseWheel.delta);
			}
		}
		
		updateWidgets(event);
	}
	
	void Row::setPosition(sf::Vector2i pos)
	{
		rect.left = pos.x;
		rect.top = pos.y;
		
		for(auto& w : getWidgets())
		{
			w->setPosition({pos.x + (static_cast<int>(w->getGlobalBounds().left) - rect.left), pos.y + (static_cast<int>(w->getGlobalBounds().top) - rect.top)});
		}
	}
	
	void Row::reposition()
	{
		int totalWidth = 0;
		for(auto& widget : getWidgets())
			totalWidth += widget->getGlobalBounds().width;
				
		for(unsigned i = 0; i < getWidgets().size(); i++)
		{
			auto& w = getWidgets()[i];
			
			sf::IntRect previousRect = (w == getWidgets()[0]) ? sf::IntRect(0, 0, 0, 0) : static_cast<sf::IntRect>(getWidgets()[i - 1]->getGlobalBounds());
			
			if(!w->isContainer())
			{
				if(totalWidth > rect.width - 2 * getBorderSize())
				{
					w->setSize({static_cast<unsigned>(rect.width / getWidgets().size() - 2 * getBorderSize()),
								static_cast<unsigned>(rect.height - 2 * getBorderSize())});
				}
				else
				{
					w->setSize({static_cast<unsigned>(w->getGlobalBounds().width),
								static_cast<unsigned>(rect.height - 2 * getBorderSize())});
				}
				
				w->setPosition({(w == getWidgets()[0] ? rect.left : previousRect.left) + getBorderSize() + previousRect.width, 
								rect.top + getBorderSize() + rect.height / 2 - static_cast<int>(w->getGlobalBounds().height / 2)});
			}
			else
			{
				if(w->getGlobalBounds().width - 2 * getBorderSize() > rect.width)
					w->setSize({static_cast<unsigned>(rect.width - 2 * getBorderSize()), static_cast<unsigned>(w->getGlobalBounds().height)});
				if(w->getGlobalBounds().height - 2 * getBorderSize() > rect.height)
					w->setSize({static_cast<unsigned>(w->getGlobalBounds().width), static_cast<unsigned>(rect.height - 2 * getBorderSize())});
				
				w->setPosition({(w == getWidgets()[0] ? rect.left : previousRect.left) + previousRect.width + getBorderSize(), 
								rect.top + getBorderSize() + (rect.height / 2) - static_cast<int>(w->getGlobalBounds().height / 2)});
				
				/*switch(w->getAlignment())
				{
					case Widget::Alignment::Center:
						w->setPosition({(w == getWidgets()[0] ? rect.left : previousRect.left) + getBorderSize() + rect.width / 2 - static_cast<int>(w->getGlobalBounds().width / 2), 
										rect.top + getBorderSize() + rect.height / 2 - static_cast<int>(w->getGlobalBounds().height / 2)});
						break;
					case Widget::Alignment::Right:
						w->setPosition({(w == getWidgets()[0] ? rect.left : previousRect.left) + rect.width - getBorderSize() - static_cast<int>(w->getGlobalBounds().width), 
										rect.top + getBorderSize() + rect.height / 2 - static_cast<int>(w->getGlobalBounds().height / 2)});
						break;
					case Widget::Alignment::Left:
						w->setPosition({(w == getWidgets()[0] ? rect.left : previousRect.left) + getBorderSize(), 
										rect.top + getBorderSize() + rect.height / 2 - static_cast<int>(w->getGlobalBounds().height / 2)});
						break;
				}*/
			}
		}
	}
	
	void Row::scroll(float amount)
	{
		// port over Column scrolling if statement
		// then figure out how to keep widgets from jumping around when scrolling
		for(auto& w : getWidgets())
		{
			w->setPosition({static_cast<int>(w->getGlobalBounds().left + amount * 10), static_cast<int>(w->getGlobalBounds().top)});
		}
	}
}
