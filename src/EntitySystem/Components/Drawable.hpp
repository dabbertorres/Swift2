#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "../Component.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace swift
{
	class Drawable : public Component
	{
		public:
			void setTexture(const sf::Texture& texture);
			void setTextureRect(const sf::Texture& texture, sf::IntRect& rect);
			
			static std::string getType();

			sf::Sprite sprite;
	};
}

#endif // DRAWABLE_HPP
