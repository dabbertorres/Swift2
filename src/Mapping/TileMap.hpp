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
			TileMap();
			~TileMap();
			
			// used in map making
			bool init();

			bool loadFile(const std::string& f);
			bool loadTexture(const sf::Texture& tex);
			
			bool saveFile(const std::string& f);
			
			void setTileNum(unsigned t, int n);
			
			void setPosition(const sf::Vector2i& pos);
			void setTileSize(const sf::Vector2u& ts);
			void setSize(const sf::Vector2u& s);
			void setTextureFile(const std::string& str);
			
			int getTileNum(unsigned t) const;
			const sf::Vector2u& getTileSize() const;
			const sf::Vector2u& getSize() const;
			const std::string& getTextureFile() const;
			unsigned getNumOfTileTypes() const;

		private:
			struct Tile
			{
				Tile(const sf::Vector2u& p)
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
			
			sf::Vector2i position;

			sf::VertexArray vertices;

			const sf::Texture* texture;
	};
}

#endif // TILEMAP_HPP
