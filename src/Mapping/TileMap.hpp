#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <string>
#include <vector>

namespace swift
{
	class TileMap : public sf::Drawable
	{
		public:
			TileMap(sf::Vector2u s);
			~TileMap();

			bool loadFile(const std::string& f);

			bool load(const sf::Texture& tex);
			
			int getTileNum(unsigned t) const;
			
			const sf::Vector2u& getTileSize() const;
			const sf::Vector2u& getSize() const;

			const std::string& getTextureFile() const;

		private:
			struct Tile
			{
				Tile(sf::Vector2u p)
					:	pos(p)
				{}
				
				sf::Vector2u pos;
			};

			void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			std::vector<Tile> tileTypes;
			std::vector<int> tiles;
			sf::Vector2u tileSize;
			sf::Vector2u sizePixels;
			sf::Vector2u sizeTiles;
			std::string textureFile;

			sf::VertexArray vertices;

			const sf::Texture* texture;
	};
}

#endif // TILEMAP_HPP
