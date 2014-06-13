#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include "../Entity.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>

#include <vector>

//typedef std::vector<bool> Bitmask;

namespace swift
{
	class Collidable
	{
		public:
			Collidable(/*const Bitmask& btm*/);
			~Collidable();
			
			static bool collision(const Collidable& one, const Collidable& two);
			
			//sf::FloatRect getBounds() const;
			
			float getRadius() const;
			
			//const Bitmask& getBitmask() const;
			
			// the texture to create a bitmask from, and the alpha threshold, below which is considered transparent
			// "SLOW"!!! As in, do this during a loading state, not during game play
			//static Bitmask makeBitmask(const sf::Texture& texture, unsigned threshold = 128);
			
		private:
			// reference, so the position updates as the sprite's position updates
			//const sf::FloatRect& bounds;
			float radius;	// length from center to top left corner
			//const Bitmask& bitmask;
	};
}

#endif // COLLIDABLE_HPP
