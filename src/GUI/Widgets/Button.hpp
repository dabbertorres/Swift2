#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../Widget.hpp" // Base class: sgui::Widget

#include <functional>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace cstr
{
	class Button : public Widget
	{
		friend class Window;
		
		public:
			Button();	// lua use only
			virtual ~Button();
			
			void setFont(const sf::Font& font);
			void setText(const std::string str);
			void setTextColor(const sf::Color& tc);
			
			void setColor(const sf::Color& c);
			
			void setFunction(const std::function<void()> f);
			
			sf::FloatRect getGlobalBounds() const;
		
		protected:
			virtual bool contains(sf::Vector2i point);
			virtual void mousePressed();
			virtual void mouseReleased();
			virtual void mouseMovedOn();
			virtual void mouseMovedOff();
			virtual void textEntered(char c);

		private:
			Button(sf::IntRect rect, const sf::Texture& tex, const std::function<void()>& f);
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			void shrinkTextToFit();
			
			sf::Sprite sprite;
			sf::Color color;
			
			std::function<void()> function;
			
			sf::Text text;
	};
}

#endif // BUTTON_HPP
