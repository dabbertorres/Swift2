#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include "../Component.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>

#include <vector>

typedef std::vector<bool> Bitmask;

namespace swift
{
	class Collidable : public Component
	{
		public:
			Collidable(const sf::Sprite& sprite, unsigned t = 128);
			~Collidable();
			
			static bool collision(const Collidable& one, const Collidable& two);
			
			sf::Vector2f getPosition() const;
			
			sf::FloatRect getBounds() const;
			
			float getRadius() const;
			
			const Bitmask& getBitmask() const;

		private:
			// the texture to create a bitmask from, and the alpha threshold, below which is considered transparent
			// "SLOW"!!! As in, do this during a loading state, not during game play
			void makeBitmask(const sf::Texture& texture, unsigned threshold);
			
			// reference, so the position updates as the sprite's position updates
			const sf::FloatRect& bounds;
			float radius;	// length from center to top left corner
			Bitmask bitmask;
	};
}

#endif // COLLIDABLE_HPP
