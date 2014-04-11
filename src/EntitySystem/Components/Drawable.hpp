#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "../Component.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace swift
{
	class Drawable : public Component, public sf::Drawable
	{
		public:
			Drawable(const sf::Texture& texture);
			~Drawable();

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			sf::Sprite sprite;
	};
}

#endif // DRAWABLE_HPP
