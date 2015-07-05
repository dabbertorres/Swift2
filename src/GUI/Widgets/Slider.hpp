#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "../Widget.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace cstr
{
	class Slider : public Widget
	{
		public:
			Slider(const sf::Vector2u& size);
			~Slider() = default;

			virtual void update(const sf::Event& event);

			virtual sf::FloatRect getGlobalBounds() const;

			virtual void setPosition(const sf::Vector2i& pos);

			virtual void setSize(const sf::Vector2u& size);

			void setValue(float v);
			float getValue() const;

			void setSliderColor(const sf::Color& c);
			void setTrackColor(const sf::Color& c);

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			bool mouseDown;

			float value;

			sf::RectangleShape track;
			sf::RectangleShape slider;
	};
}

#endif // SLIDER_HPP
