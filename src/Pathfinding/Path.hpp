#ifndef PATH_H
#define PATH_H

#include <deque>

#include <SFML/System/Vector2.hpp>
#include "../Mapping/TileMap.hpp"

namespace swift
{
	class Path
	{
		public:
			using PathNodes = std::deque<sf::Vector2f>;
			
			Path(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Vector2u& size, unsigned int layer, const TileMap& map);
			
			const PathNodes& getNodes() const;
			
		private:
			void calculate(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Vector2u& size, unsigned int layer, const TileMap& map);
			
			static constexpr float PATH_STEP = 4.f;
			
			PathNodes nodes;
	};
}

#endif // PATH_H
