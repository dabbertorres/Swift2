#include "Path.hpp"

#include "../Math/Math.hpp"

#include <vector>
#include <algorithm>

namespace swift
{
	Path::Path(const sf::Vector2u& start, const sf::Vector2u& end, const NodesMap& nodes)
	:	pathFound(false)
	{
		calculate(start, end, nodes);
	}

	const Path::PathNodes& Path::getNodes() const
	{
		return nodes;
	}

	void Path::calculate(const sf::Vector2u& start, const sf::Vector2u& end, const NodesMap& nodeMap)
	{
		std::vector<sf::Vector2u> visited;

		nodes.push_back(start);
		visited.push_back(start);

		buildPathMap(start, end, nodes, visited, nodeMap);

		if(!pathFound)
			nodes.clear();
		else
		{
			// find the path with the smallest distance, set the nodes to it
			nodes = *std::min_element(possiblePaths.begin(), possiblePaths.end(), [](const PathNodes& one, const PathNodes& two)
			{
				return one.size() < two.size();
			});
		}
	}

	void Path::buildPathMap(const sf::Vector2u& start, const sf::Vector2u& end, const PathNodes& path, std::vector<sf::Vector2u>& visited, const NodesMap& nodeMap)
	{
		// check if we've reached the end (in the same tile as the end position
		if(path.back().getPosition() == end)
		{
			// if so, add path to the list of possible paths and return
			possiblePaths.push_back(path);
			pathFound = true;
			return;
		}

		struct NewNode
		{
			sf::Vector2u position;
			PathNodes path;
		};

		std::vector<NewNode> neighbors;
		std::vector<NewNode> validNeighbors;

		neighbors.emplace_back();	// top
		neighbors.emplace_back();	// bottom
		neighbors.emplace_back();	// left
		neighbors.emplace_back();	// right

		neighbors[0].position = start - sf::Vector2u{0, 1};
		neighbors[1].position = start + sf::Vector2u{0, 1};
		neighbors[2].position = start - sf::Vector2u{1, 0};
		neighbors[3].position = start + sf::Vector2u{1, 0};
		
		for(int i = 0; i < 4; i++)
		{
			if(neighbors[i].position.x >= nodeMap.size() || neighbors[i].position.y > nodeMap[neighbors[i].position.x].size())
			{
				neighbors.erase(neighbors.begin());
				i--;
			}
		}

		// check if positions are valid tiles, if they are passable, and if they haven't already been visited
		// if so, add them to the neighbors vector
		// also, save copying until now. Less copying that way
		for(auto& n : neighbors)
		{
			if(nodeMap[n.position.x][n.position.y] && std::find(visited.begin(), visited.end(), n.position) == visited.end())
			{
				n.path = path;
				n.path.push_back(n.position);
				validNeighbors.push_back(n);
				visited.push_back(n.position);
			}
		}

		// recursive across all valid neighbors
		for(auto& n : validNeighbors)
		{
			buildPathMap(n.position, end, n.path, visited, nodeMap);
		}
	}

	sf::Vector2f Path::getTileCenter(const sf::Vector2f& pos, const sf::Vector2u& tileSize)
	{
		return {static_cast<unsigned int>(pos.x / tileSize.x) * tileSize.x + tileSize.x / 2.f, static_cast<unsigned int>(pos.y / tileSize.y) * tileSize.y + tileSize.y / 2.f};
	}
}
