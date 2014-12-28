#include "Path.hpp"

#include "../Math/Math.hpp"

namespace swift
{
	Path::Path(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Vector2u& size, unsigned int layer, const TileMap& map)
	{
		calculate(start, end, size, layer, map);
	}

	const Path::PathNodes& Path::getNodes() const
	{
		return nodes;
	}

	void Path::calculate(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Vector2u& size, unsigned int layer, const TileMap& map)
	{
		sf::Vector2u tileSize = map.getTileSize();

		sf::Vector2f directionToEnd = math::unit(end - start);

		nodes.push_back(start);

		while(math::distanceSquared(nodes.back(), end) > PATH_STEP * PATH_STEP)
		{
			directionToEnd = math::unit(end - nodes.back());
			sf::Vector2f test = nodes.back() + directionToEnd * PATH_STEP;
			
			nodes.push_back(test);
		}
	}
}
