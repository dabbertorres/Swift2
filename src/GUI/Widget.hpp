#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace cstr
{
	class Widget : public sf::Drawable
	{
		friend class Window;
		
		public:
			Widget() {};
			virtual ~Widget() {};
			
			virtual bool getState() const
			{
				return false;
			}
			
			virtual sf::FloatRect getGlobalBounds() const = 0;
			
		protected:
			virtual bool contains(sf::Vector2i point) = 0;
			virtual void mousePressed() = 0;
			virtual void mouseReleased() = 0;
			virtual void mouseMovedOn() = 0;
			virtual void mouseMovedOff() = 0;
			virtual void textEntered(char c) = 0;
		
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}

#endif // WIDGET_HPP
