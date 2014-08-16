#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <string>

namespace swift
{
	class TileMap : public sf::Drawable
	{
		public:
			TileMap();
			~TileMap();
			
			bool load(const sf::Texture& tex, sf::Vector2u tileSize, const std::vector<int>& tiles, unsigned width, unsigned height);
			
			void setTexture(const sf::Texture& texture);

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			sf::VertexArray vertices;
			
			const sf::Texture* texture;
	};
}

#endif // TILEMAP_HPP
