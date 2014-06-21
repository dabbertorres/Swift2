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
			
			bool getState() const;
			void setState(bool s);
			
			sf::FloatRect getGlobalBounds() const;
			
		protected:
			bool contains(sf::Vector2i point);
			void mousePressed();
			void mouseReleased();
			void mouseMovedOn();
			void mouseMovedOff();
			void textEntered(char c);

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
			sf::Sprite sprite;
			sf::Color color;
			
			const sf::Texture& offTex;
			const sf::Texture& onTex;
			
			bool state;
	};
}

#endif // TOGGLE_HPP
