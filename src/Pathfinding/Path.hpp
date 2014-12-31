#ifndef PATH_H
#define PATH_H

#include <deque>

#include <SFML/System/Vector2.hpp>
#include "../Mapping/TileMap.hpp"
#include "Node.hpp"

namespace swift
{
	class Path
	{
		public:
			using PathNodes = std::deque<Node>;
			
			Path(const sf::Vector2f& start, const sf::Vector2f& end, unsigned int layer, const TileMap& map);
			
			const PathNodes& getNodes() const;
			
		private:
			void calculate(const sf::Vector2f& start, const sf::Vector2f& end, unsigned int layer, const TileMap& map);
			
			void buildPathMap(const sf::Vector2f& center, const sf::Vector2f& end, const PathNodes& path, std::vector<sf::Vector2u> visited, unsigned int layer, const TileMap& map);
			
			static sf::Vector2f getTileCenter(const sf::Vector2f& pos, const sf::Vector2u& tileSize);
			
			PathNodes nodes;
			
			bool pathFound;
	};
}

#endif // PATH_H
