#ifndef LAYER_HPP
#define LAYER_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <vector>

#include "Tile.hpp"

namespace swift
{
	class Layer : public sf::Drawable
	{
		friend class TileMap;
		public:
			Layer(const sf::Vector2u& s, const sf::Vector2u& ts);
			
			void update(float dt);
			
			void addTile(const sf::Vector2u& texPos, const sf::Vector2u& texSize, bool p, int i);
			
			unsigned int getNumTiles() const;
			
			const Tile* getTile(unsigned int t) const;
			const Tile* getTile(const sf::Vector2f& pos) const;

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			sf::VertexArray vertices;

			std::vector<Tile> tiles;
			
			sf::Vector2u size;
			sf::Vector2u tileSize;
	};
}

#endif // LAYER_HPP
