#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "../Widget.hpp"

#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace cstr
{
	class TextBox : public Widget
	{
		public:
			TextBox(const sf::Vector2u& size, sf::Font& f, const std::string& d = "");
			~TextBox() = default;

			virtual void update(const sf::Event& event);
			
			virtual sf::FloatRect getGlobalBounds() const;

			virtual void setPosition(const sf::Vector2i& pos);

			virtual void setSize(const sf::Vector2u& size);
			
			const std::string& getString() const;
			
			void clear();
			
			void setTextColor(const sf::Color& tc);
			
			void setOutlineColor(const sf::Color& oc);
			
			void setBackgroundColor(const sf::Color& bc);

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			void setDisplayedString();
			
			std::string currentStr;
			int cursorPosition;
			
			bool selected;
			
			sf::Text text;
			
			sf::RectangleShape border;
	};
}

#endif // TEXTBOX_HPP
