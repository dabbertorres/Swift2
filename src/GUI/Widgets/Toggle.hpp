#ifndef TOGGLE_HPP
#define TOGGLE_HPP

#include "../Widget.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <functional>

namespace cstr
{
	class Toggle : public Widget
	{
		public:
			Toggle(sf::Vector2u size, const sf::Texture& on, const sf::Texture& off, bool s, std::function<void(bool s)> c);
			~Toggle();
			
			bool getState() const;

			virtual void update(sf::Event& event);

			virtual sf::FloatRect getGlobalBounds() const;

			virtual void setPosition(sf::Vector2i pos);

			virtual void setSize(sf::Vector2u size);

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			sf::Sprite sprite;
			sf::Color baseColor;
			const sf::Texture& onTex;
			const sf::Texture& offTex;
			
			std::function<void(bool s)> callback;
			
			bool state;
	};
}

#endif // TOGGLE_HPP
