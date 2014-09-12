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
			TextBox(sf::Vector2u size, sf::Font& f, const std::string& d, const std::string& c = "");
			~TextBox();

			virtual void update(sf::Event& event);
			
			virtual sf::FloatRect getGlobalBounds() const;

			virtual void setPosition(sf::Vector2i pos);

			virtual void setSize(sf::Vector2u size);
			
			const std::string& getString() const;
			
			void setTextColor(const sf::Color& tc);
			
			void setOutlineColor(const sf::Color& oc);
			
			void setBackgroundColor(const sf::Color& bc);

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			std::string defaultStr;
			std::string currentStr;
			
			bool selected;
			
			sf::Text text;
			
			sf::RectangleShape border;
	};
}

#endif // TEXTBOX_HPP
