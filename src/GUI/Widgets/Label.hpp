#ifndef LABEL_HPP
#define LABEL_HPP

#include "../Widget.hpp" // Base class: sgui::Widget

#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace cstr
{
	class Label : public Widget
	{
		public:
			Label(const sf::Vector2f& pos, const std::string& str, const sf::Font& font);
			virtual ~Label();
			
			void setFont(const sf::Font& font);
			void setText(const std::string& str);
			void setTextColor(const sf::Color& tc);
			void setCharacterSize(unsigned size);
			
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
			
			sf::Text text;
			sf::Vector2f position;
	};
}

#endif // LABEL_HPP
