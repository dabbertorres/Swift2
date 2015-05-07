#ifndef PATH_H
#define PATH_H

#include <deque>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include "../Mapping/TileMap.hpp"
#include "Node.hpp"

namespace swift
{
	class Path
	{
		public:
			using PathNodes = std::deque<Node>;
			using NodesMap = std::vector<std::vector<bool>>;
			
			Path(const sf::Vector2u& start, const sf::Vector2u& end, const NodesMap& nodeMap);
			
			const PathNodes& getNodes() const;
			
		private:
			void calculate(const sf::Vector2u& start, const sf::Vector2u& end, const NodesMap& nodeMap);
			
			void buildPathMap(const sf::Vector2u& start, const sf::Vector2u& end, const PathNodes& path, std::vector<sf::Vector2u>& visited, const NodesMap& nodes);
			
			static sf::Vector2f getTileCenter(const sf::Vector2f& pos, const sf::Vector2u& tileSize);
			
			PathNodes nodes;
			
			std::vector<PathNodes> possiblePaths;
			
			bool pathFound;
	};
}

#endif // PATH_H
