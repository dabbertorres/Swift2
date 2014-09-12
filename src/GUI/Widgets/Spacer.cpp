#include "Spacer.hpp"
//#include <SFML/Graphics/RectangleShape.hpp>
namespace cstr
{
	Spacer::Spacer(sf::Vector2i size)
	{
		this->setSize(static_cast<sf::Vector2u>(size));
	}

	Spacer::~Spacer()
	{
	}
	
	void Spacer::update(sf::Event& /*event*/)
	{
		// do nothing
	}
	
	sf::FloatRect Spacer::getGlobalBounds() const
	{
		return static_cast<sf::FloatRect>(rect);
	}
	
	void Spacer::draw(sf::RenderTarget& /*target*/, sf::RenderStates /*states*/) const
	{
		/* debug drawing
		sf::RectangleShape fill({rect.width, rect.height});
		fill.setFillColor(sf::Color::Green);
		fill.setPosition({rect.left, rect.top});
		target.draw(fill, states);*/
		// do nothing
	}
}
