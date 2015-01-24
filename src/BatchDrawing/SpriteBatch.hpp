#ifndef SPRITEBATCH_HPP
#define SPRITEBATCH_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <array>
#include <queue>
#include <vector>

namespace swift
{
	class SpriteBatch : public sf::Drawable
	{
		public:
			SpriteBatch(const sf::Texture& tex, unsigned int s);
			
			void update();
			
			const std::vector<sf::Vertex>& getVertices() const;

			std::array<sf::Vertex*, 4> addSprite();
			sf::Vector2u getTextureSize() const;

		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			std::vector<sf::Vertex> vertices;
			const sf::Texture& texture;
			unsigned int spriteNum;
			std::queue<unsigned int> notUsed;	// for checking which vertices are not in use, for reusing them
	};
}

#endif // SPRITEBATCH_HPP
