#ifndef SPRITEBATCH_HPP
#define SPRITEBATCH_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <array>
#include <vector>

#include "Sprite.hpp"

namespace swift
{
	class SpriteBatch : public sf::Drawable
	{
		public:
			SpriteBatch(const sf::Texture& tex);
			
			const std::vector<sf::Vertex>& getVertices() const;

			Sprite addSprite(const sf::FloatRect& texRect = {-1, -1, -1, -1});
			sf::Vector2u getTextureSize() const;
			
			sf::Vertex* getVertex(std::size_t i);
			void remove(const std::array<std::size_t, 4>& verts);

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			std::vector<sf::Vertex> vertices;
			const sf::Texture& texture;
	};
}

#endif // SPRITEBATCH_HPP
