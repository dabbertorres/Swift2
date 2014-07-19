#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "../Widget.hpp" // Base class: sgui::Widget

#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace cstr
{
	class TextBox : public Widget
	{
		public:
			TextBox(const sf::IntRect& ir, const sf::Color& in, const sf::Color& out, const sf::Font& f);
			~TextBox();
			
			void setFont(const sf::Font& font);
			void setTextColor(const sf::Color& tc);
			void setCharacterSize(unsigned size);
			
			const std::string& getString() const;
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
			
			sf::RectangleShape rect;
			std::string string;
			sf::Text text;
	};
}

#endif // TEXTBOX_HPP
