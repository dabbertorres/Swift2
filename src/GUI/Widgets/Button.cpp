#include "Button.hpp"

namespace cstr
{
	const sf::Color COLOR_CHANGE = {40, 40, 40, 0};
	
	Button::Button(sf::Vector2u size, const sf::Texture& tex, const std::function<void()>& f)
		:	baseColor({128, 128, 128}),
			string(""),
			callback(f)
	{
		sprite.setTexture(tex);
		sprite.setColor(baseColor);
		sprite.setScale(size.x / sprite.getGlobalBounds().width, size.y / sprite.getGlobalBounds().height);
	}

	Button::~Button()
	{
	}

	void Button::update(sf::Event& event)
	{
		switch(event.type)
		{
			case sf::Event::MouseMoved:
				if(sprite.getGlobalBounds().contains({static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)}))
				{
					mouseOn = true;
					sprite.setColor(baseColor + COLOR_CHANGE);
				}
				else
				{
					mouseOn = false;
					sprite.setColor(baseColor);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if(mouseOn)
				{
					sprite.setColor(baseColor - COLOR_CHANGE);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if(mouseOn)
				{
					callback();
					sprite.setColor(baseColor);
				}
				break;
			default:
				break;
		}
	}
	
	void Button::call()
	{
		callback();
	}

	sf::FloatRect Button::getGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}
	
	void Button::setString(const std::string& str, const sf::Font& f)
	{
		string = str;
		text.setFont(f);
		text.setString(string);
		text.setCharacterSize(sprite.getGlobalBounds().height);
		if(sprite.getGlobalBounds().width < text.getGlobalBounds().width)
			text.setCharacterSize(text.getCharacterSize() * (sprite.getGlobalBounds().width - 2) / text.getGlobalBounds().width);
		
		text.setOrigin({text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2});
		text.setPosition({sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2});
	}
	
	void Button::setString(const std::string& str)
	{
		setString(str, *text.getFont());
	}
	
	const std::string& Button::getString() const
	{
		return string;
	}
	
	void Button::setPosition(sf::Vector2i pos)
	{
		sprite.setPosition(static_cast<sf::Vector2f>(pos));
		text.setPosition({sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2});
	}
	
	void Button::setSize(sf::Vector2u size)
	{
		sprite.scale(size.x / sprite.getGlobalBounds().width, size.y / sprite.getGlobalBounds().height);
		
		if(string != "")
			setString(string, *text.getFont());
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
		if(string.length() > 0)
			target.draw(text, states);
	}
}
