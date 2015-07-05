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
			Button(const sf::Vector2u& size, const sf::Texture& tex, const std::function<void()>& f);
			~Button() = default;
			
			virtual void update(const sf::Event& event);
			
			void call();

			virtual sf::FloatRect getGlobalBounds() const;
			
			void setString(const std::string& str, const sf::Font& f, unsigned ts = 0);
			void setString(const std::string& str, unsigned ts = 0);
			
			const std::string& getString() const;
			
			virtual void setPosition(const sf::Vector2i& pos);
			
			virtual void setSize(const sf::Vector2u& size);
			
			virtual void setTextureRect(const sf::IntRect& rect, const sf::Vector2f& size);

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			sf::Sprite sprite;
			sf::Text text;
			sf::Color baseColor;
			std::string string;
			std::function<void()> callback;
			unsigned textSize;
	};
}

#endif // BUTTON_HPP
