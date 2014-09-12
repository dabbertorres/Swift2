#include "Column.hpp"
#include <iostream>
namespace cstr
{
	Column::Column(sf::IntRect r, bool s)
		:	Container(r, s)
	{
	}
	
	Column::Column(sf::Vector2i size, bool s)
		:	Container(size, s)
	{
	}

	Column::~Column()
	{
	}
	
	void Column::update(sf::Event& event)
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
	
	void Column::setPosition(sf::Vector2i pos)
	{
		rect.left = pos.x;
		rect.top = pos.y;
		
		for(auto& w : getWidgets())
		{
			w->setPosition({pos.x + (static_cast<int>(w->getGlobalBounds().left) - rect.left), pos.y + (static_cast<int>(w->getGlobalBounds().top) - rect.top)});
		}
	}
	
	void Column::reposition()
	{
		int totalHeight = 0;
		for(auto& widget : getWidgets())
			totalHeight += widget->getGlobalBounds().height;
		
		for(unsigned i = 0; i < getWidgets().size(); i++)
		{
			auto& w = getWidgets()[i];
			
			sf::IntRect previousRect = (w == getWidgets()[0]) ? sf::IntRect(0, 0, 0, 0) : static_cast<sf::IntRect>(getWidgets()[i - 1]->getGlobalBounds());
			
			if(!w->isContainer())
			{
				if(totalHeight > rect.height - 2 * getBorderSize())
				{
					w->setSize({static_cast<unsigned>(rect.width - 2 * getBorderSize()),
								static_cast<unsigned>(rect.height / getWidgets().size() - 2 * getBorderSize())});
				}
				else
				{
					w->setSize({static_cast<unsigned>(rect.width - 2 * getBorderSize()),
								static_cast<unsigned>(w->getGlobalBounds().height)});
				}
				
				w->setPosition({rect.left + getBorderSize() + rect.width / 2 - static_cast<int>(w->getGlobalBounds().width / 2),
								(w == getWidgets()[0] ? rect.top : previousRect.top) + getBorderSize() + previousRect.height});
			}
			else
			{
				if(w->getGlobalBounds().width - 2 * getBorderSize() > rect.width)
					w->setSize({static_cast<unsigned>(rect.width - 2 * getBorderSize()), static_cast<unsigned>(w->getGlobalBounds().height)});
				if(w->getGlobalBounds().height - 2 * getBorderSize() > rect.height)
					w->setSize({static_cast<unsigned>(w->getGlobalBounds().width), static_cast<unsigned>(rect.height - 2 * getBorderSize())});
				
				w->setPosition({rect.left + getBorderSize() + rect.width / 2 - static_cast<int>(w->getGlobalBounds().width / 2),
								(w == getWidgets()[0] ? rect.top : previousRect.top) + getBorderSize() + previousRect.height});
				
				/*switch(w->getAlignment())
				{
					case Widget::Alignment::Center:
						w->setPosition({rect.left + getBorderSize() + rect.width / 2 - static_cast<int>(w->getGlobalBounds().width / 2), 
										(w == getWidgets()[0] ? rect.top : previousRect.top) + getBorderSize() + previousRect.height});
						break;
					case Widget::Alignment::Right:
						w->setPosition({rect.left + rect.width - getBorderSize() - static_cast<int>(w->getGlobalBounds().width), 
										(w == getWidgets()[0] ? rect.top : previousRect.top) + getBorderSize() + previousRect.height});
						break;
					case Widget::Alignment::Left:
						w->setPosition({rect.left + getBorderSize(), (w == getWidgets()[0] ? rect.top : previousRect.top) + getBorderSize() + previousRect.height});
						break;
				}*/
			}
		}
	}
	
	void Column::scroll(float amount)
	{
		if(getWidgets().size() > 0)
		{
			if((!(getWidgets()[0]->getGlobalBounds().top <= rect.top) && amount > 0) || 
				(!(getWidgets()[getWidgets().size() - 1]->getGlobalBounds().top + getWidgets()[getWidgets().size() - 1]->getGlobalBounds().height >= rect.top + rect.height) && amount < 0))
			{
				for(auto& w : getWidgets())
				{
					w->setPosition({static_cast<int>(w->getGlobalBounds().left), static_cast<int>(w->getGlobalBounds().top - amount * 10)});
				}
			}
		}
	}
}
