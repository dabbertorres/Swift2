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
#include <map>

#include "Layer.hpp"

namespace swift
{
	class TileMap : public sf::Drawable
	{
		public:
			TileMap();
			~TileMap();
			
			void update(float dt);

			bool loadFile(const std::string& f);
			bool loadTexture(const sf::Texture& tex);

			void setTileSize(const sf::Vector2u& ts);
			void setSize(const sf::Vector2u& s);
			void setTextureFile(const std::string& str);

			const Tile* getTile(unsigned int t, unsigned int l) const;
			const Tile* getTile(const sf::Vector2f& pos, unsigned int l) const;
			
			sf::Vector2u getTileSize() const;
			sf::Vector2u getSize() const;
			std::string getTextureFile() const;
			unsigned int getNumOfTileTypes() const;

		private:
			struct TileType
			{
				bool passable;
				unsigned int zIndex;
				bool animated;
				sf::Vector2u texPos;
			};

			void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			std::map<unsigned int, TileType> tileTypes;
			std::vector<Layer> layers;

			sf::Vector2u tileSize;
			sf::Vector2u sizePixels;
			sf::Vector2u sizeTiles;
			sf::Vector2u textureSize;
			sf::Vector2u textureTileSize;
			std::string textureFile;

			const sf::Texture* texture;
	};
}

#endif // TILEMAP_HPP
