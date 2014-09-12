#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../Widget.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>

#include <functional>
#include <string>

namespace cstr
{
	class Button : public Widget
	{
		public:
			Button(sf::Vector2u size, const sf::Texture& tex, const std::function<void()>& f);
			~Button();
			
			virtual void update(sf::Event& event);
			
			void call();

			virtual sf::FloatRect getGlobalBounds() const;
			
			void setString(const std::string& str, const sf::Font& f);
			void setString(const std::string& str);
			
			const std::string& getString() const;
			
			virtual void setPosition(sf::Vector2i pos);
			
			virtual void setSize(sf::Vector2u size);

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			sf::Sprite sprite;
			sf::Text text;
			sf::Color baseColor;
			std::string string;
			std::function<void()> callback;
	};
}

#endif // BUTTON_HPP
