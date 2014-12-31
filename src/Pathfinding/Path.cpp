#include "Path.hpp"

#include "../Math/Math.hpp"

#include <vector>
#include <algorithm>

namespace swift
{
	Path::Path(const sf::Vector2f& start, const sf::Vector2f& end, unsigned int layer, const TileMap& map)
		:	pathFound(false)
	{
		calculate(start, end, layer, map);
	}

	const Path::PathNodes& Path::getNodes() const
	{
		return nodes;
	}

	void Path::calculate(const sf::Vector2f& start, const sf::Vector2f& end, unsigned int layer, const TileMap& map)
	{
		sf::Vector2u tileSize = map.getTileSize();

		std::vector<sf::Vector2u> visited;

		nodes.push_back(start);
		visited.push_back( {static_cast<unsigned int>(start.x / tileSize.x), static_cast<unsigned int>(start.y / tileSize.y)});

		sf::Vector2f center = getTileCenter(nodes.back().getPosition(), tileSize);

		nodes.push_back(center);
		visited.push_back( {static_cast<unsigned int>(center.x / tileSize.x), static_cast<unsigned int>(center.y / tileSize.y)});

		buildPathMap(center, end, nodes, visited, layer, map);

		if(!pathFound)
			nodes.clear();
		else
		{
			// find the path with the smallest distance, set the nodes to it
			nodes = *std::min_element(possiblePaths.begin(), possiblePaths.end(), [](const PathNodes& one, const PathNodes& two)
			{
				float oneTotal = 0;
				for(unsigned int i = 0; i < one.size() - 1; i++)
				{
					oneTotal += math::distance(one[i + 1].getPosition(), one[i].getPosition());
				}

				float twoTotal = 0;
				for(unsigned int i = 0; i < two.size() - 1; i++)
				{
					twoTotal += math::distance(two[i + 1].getPosition(), two[i].getPosition());
				}

				return oneTotal < twoTotal;
			});
		}
	}

	void Path::buildPathMap(const sf::Vector2f& center, const sf::Vector2f& end, const PathNodes& path, std::vector<sf::Vector2u> visited, unsigned int layer, const TileMap& map)
	{
		sf::Vector2u tileSize = map.getTileSize();

		// check if we've reached the end
		if(math::distanceSquared(path.back().getPosition(), end) <= tileSize.x * tileSize.x / 2.f)
		{
			// if so, add path to the list of possible paths and return
			possiblePaths.push_back(path);
			pathFound = true;
			return;
		}

		struct NewNode
		{
			sf::Vector2f position;
			const Tile* tile;
			PathNodes path;
		};

		std::vector<NewNode> neighbors;
		std::vector<NewNode> validNeighbors;

		neighbors.emplace_back();	// top
		neighbors.emplace_back();	// bottom
		neighbors.emplace_back();	// left
		neighbors.emplace_back();	// right

		neighbors[0].position = {center - sf::Vector2f(0, tileSize.y)};
		neighbors[1].position = {center + sf::Vector2f(0, tileSize.y)};
		neighbors[2].position = {center - sf::Vector2f(tileSize.x, 0)};
		neighbors[3].position = {center + sf::Vector2f(tileSize.x, 0)};

		// check if positions are valid tiles, if they are passable, and if they haven't already been visited
		// if so, add them to the neighbors vector
		// also, save copying until now. Less copying that way
		for(auto& n : neighbors)
		{
			n.tile = map.getTile(n.position, 0);

			sf::Vector2u tilePos = {static_cast<unsigned int>(n.position.x / tileSize.x), static_cast<unsigned int>(n.position.y / tileSize.y)};

			if(n.tile && n.tile->isPassable() && std::find(visited.begin(), visited.end(), tilePos) == visited.end())
			{
				n.path = path;
				n.path.push_back(n.position);
				validNeighbors.push_back(n);
				visited.push_back(tilePos);
			}
		}

		// recursive across all valid neighbors
		for(auto& n : validNeighbors)
		{
			buildPathMap(n.position, end, n.path, visited, layer, map);
		}
	}

	sf::Vector2f Path::getTileCenter(const sf::Vector2f& pos, const sf::Vector2u& tileSize)
	{
		return {static_cast<unsigned int>(pos.x / tileSize.x) * tileSize.x + tileSize.x / 2.f, static_cast<unsigned int>(pos.y / tileSize.y) * tileSize.y + tileSize.y / 2.f};
	}
}
