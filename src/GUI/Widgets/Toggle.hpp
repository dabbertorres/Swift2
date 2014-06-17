#ifndef TOGGLE_HPP
#define TOGGLE_HPP

#include "../Widget.hpp" // Base class: sgui::Widget

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace cstr
{
	class Toggle : public Widget
	{
		public:
			Toggle(sf::IntRect rect, const sf::Texture& off, const sf::Texture& on, bool s);
			~Toggle();
			
			virtual bool getState() const;
			void setState(bool s);
			
			sf::FloatRect getGlobalBounds() const;
			
		protected:
			virtual bool contains(sf::Vector2i point);
			virtual void mousePressed();
			virtual void mouseReleased();
			virtual void mouseMovedOn();
			virtual void mouseMovedOff();
			virtual void textEntered(char c);

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
			sf::Sprite sprite;
			sf::Color color;
			
			const sf::Texture& offTex;
			const sf::Texture& onTex;
			
			bool state;
	};
}

#endif // TOGGLE_HPP
