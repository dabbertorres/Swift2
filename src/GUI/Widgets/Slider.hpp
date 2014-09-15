#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "../Widget.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace cstr
{
	class Slider : public Widget
	{
		public:
			Slider(sf::Vector2u size);
			~Slider();

			virtual void update(sf::Event& event);

			virtual sf::FloatRect getGlobalBounds() const;

			virtual void setPosition(sf::Vector2i pos);

			virtual void setSize(sf::Vector2u size);

			void setValue(float v);
			float getValue() const;

			void setSliderColor(sf::Color c);
			void setTrackColor(sf::Color c);

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			bool mouseDown;

			float value;

			sf::RectangleShape track;
			sf::RectangleShape slider;
	};
}

#endif // SLIDER_HPP
