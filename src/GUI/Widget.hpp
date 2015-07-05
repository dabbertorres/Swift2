#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Event.hpp>

namespace cstr
{
	class Widget : public sf::Drawable
	{
		public:
			enum class Alignment
			{
			    Left,
			    Center,
			    Right
			};

			Widget()
			:	mouseOn(false),
				rect(0, 0, 0, 0),
				alignment(Alignment::Center)
			{}
			
			Widget(const sf::IntRect& r)
			:	mouseOn(false),
				rect(r),
				alignment(Alignment::Center)
			{}
			
			virtual ~Widget()
			{}

			virtual void update(const sf::Event& event) = 0;

			virtual sf::FloatRect getGlobalBounds() const
			{
				return static_cast<sf::FloatRect>(rect);
			}
			
			virtual bool isContainer() const
			{
				return false;
			}

			void setAlignment(Alignment a)
			{
				alignment = a;
			}

			Alignment getAlignment() const
			{
				return alignment;
			}
			
			virtual void setPosition(const sf::Vector2i& pos)
			{
				rect.left = pos.x;
				rect.top = pos.y;
			}
			
			virtual void setSize(const sf::Vector2u& size)
			{
				rect.width = size.x;
				rect.height = size.y;
			}

		protected:
			bool mouseOn;
			sf::IntRect rect;
			
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

			Alignment alignment;
	};
}

#endif // WIDGET_HPP
