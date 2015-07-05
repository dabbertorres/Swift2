#include "Spacer.hpp"
//#include <SFML/Graphics/RectangleShape.hpp>
namespace cstr
{
	Spacer::Spacer(const sf::Vector2i& size)
	{
		this->setSize(static_cast<sf::Vector2u>(size));
	}
	
	void Spacer::update(const sf::Event&)
	{}
	
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
