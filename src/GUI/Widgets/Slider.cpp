#include "Slider.hpp"

namespace cstr
{
	Slider::Slider(sf::Vector2u size)
		:	Widget({0, 0, static_cast<int>(size.x), static_cast<int>(size.y)}),
			mouseDown(false)
	{
		slider.setFillColor({128, 128, 128});
		track.setFillColor({128, 128, 128});
		track.setSize({static_cast<float>(size.x), static_cast<float>(size.y) / 3});
		slider.setSize({static_cast<float>(size.x / 10), static_cast<float>(size.y)});
	}

	Slider::~Slider()
	{
	}
	
	void Slider::update(sf::Event& event)
	{
		switch(event.type)
		{
			case sf::Event::MouseMoved:
				if(mouseDown)
				{
					if(track.getGlobalBounds().left - slider.getGlobalBounds().width / 2 <= event.mouseMove.x && 
					event.mouseMove.x <= track.getGlobalBounds().left + track.getGlobalBounds().width - slider.getGlobalBounds().width / 2)
						slider.setPosition(event.mouseMove.x - slider.getGlobalBounds().width / 2, slider.getGlobalBounds().top);
					else if(event.mouseMove.x <= track.getGlobalBounds().left - slider.getGlobalBounds().width / 2)
						slider.setPosition(track.getGlobalBounds().left - slider.getGlobalBounds().width / 2, slider.getGlobalBounds().top);
					else
						slider.setPosition(track.getGlobalBounds().left + track.getGlobalBounds().width - slider.getGlobalBounds().width / 2, slider.getGlobalBounds().top);
						
					value = (slider.getGlobalBounds().left + slider.getGlobalBounds().width / 2 - track.getGlobalBounds().left) / track.getGlobalBounds().width;
				}
				break;
			case sf::Event::MouseButtonPressed:
				if(slider.getGlobalBounds().contains({static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)}))
				{
					mouseDown = true;
				}
				break;
			case sf::Event::MouseButtonReleased:
				mouseDown = false;
			default:
				break;
		}
	}
	
	sf::FloatRect Slider::getGlobalBounds() const
	{
		return {track.getGlobalBounds().left, slider.getGlobalBounds().top, track.getGlobalBounds().width, slider.getGlobalBounds().height};
	}
	
	void Slider::setPosition(sf::Vector2i pos)
	{
		slider.setPosition(pos.x + slider.getPosition().x - track.getPosition().x, pos.y);
		track.setPosition(pos.x, pos.y + slider.getSize().y / 3);
	}
	
	void Slider::setSize(sf::Vector2u size)
	{
		track.setSize({static_cast<float>(size.x), static_cast<float>(size.y) / 3});
		slider.setSize({static_cast<float>(size.x / 20), static_cast<float>(size.y)});
	}
	
	void Slider::setValue(float v)
	{
		if(0 <= v && v <= 1)
		{
			value = v;
			slider.setPosition(track.getPosition().x + track.getGlobalBounds().width * value, slider.getPosition().y);
		}
	}
	
	float Slider::getValue() const
	{
		return value;
	}
	
	void Slider::setSliderColor(sf::Color c)
	{
		slider.setFillColor(c);
	}
	
	void Slider::setTrackColor(sf::Color c)
	{
		track.setFillColor(c);
	}
	
	void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(track, states);
		target.draw(slider, states);
	}
}
