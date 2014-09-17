#ifndef MAINWORLD_HPP
#define MAINWORLD_HPP

#include "../World.hpp"

#include "../../Mapping/TileMap.hpp"

namespace swift
{
	class TestWorld : public World
	{
		public:
			TestWorld(const sf::Vector2i& s, AssetManager& am);

			virtual void update(float dt);

			virtual void draw(sf::RenderTarget& target);
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states);

			virtual bool load(const std::string& file);

			virtual bool save(const std::string& file);

			TileMap tilemap;
	};
}

#endif // MAINWORLD_HPP
