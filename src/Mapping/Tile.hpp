#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>

namespace swift
{
	class Tile
	{
		public:
			Tile(const sf::Vector2u& texPos, const sf::Vector2u& texSize, bool p, unsigned int z, unsigned int i);
			
			void update(float dt);
			void addFrame(const sf::IntRect& r);
			
			void setAnimated(bool a);
			bool isAnimated() const;
			
			void setAnimationTime(float t);
			
			bool isPassable() const;
			
			unsigned int getZindex() const;
			
			unsigned int getID() const;

		private:
			std::vector<sf::IntRect> texRects;
			unsigned int frameNum;
			
			bool passable;
			
			bool animated;
			float animationTime;
			float currentTime;
			
			unsigned int zIndex;
			
			unsigned int id;
	};
}

#endif // TILE_HPP
