#include "SpriteBatch.hpp"

namespace swift
{
	SpriteBatch::SpriteBatch(const sf::Texture& tex)
	:	texture(tex)
	{}
	
	const std::vector<sf::Vertex>& SpriteBatch::getVertices() const
	{
		return vertices;
	}

	Sprite SpriteBatch::addSprite(const sf::FloatRect& texRect)
	{
		std::array<std::size_t, 4> verts;
		
		for(auto& v : verts)
		{
			vertices.emplace_back();
			v = vertices.size() - 1;
		}
		
		if(texRect != sf::FloatRect{-1, -1, -1, -1})
		{
			vertices[vertices.size() - 4].texCoords = {texRect.left, texRect.top};
			vertices[vertices.size() - 3].texCoords = {texRect.left + texRect.width, texRect.top};
			vertices[vertices.size() - 2].texCoords = {texRect.left + texRect.width, texRect.top + texRect.height};
			vertices[vertices.size() - 1].texCoords = {texRect.left, texRect.top + texRect.height};
		}
		else
		{
			vertices[vertices.size() - 4].texCoords = {0, 0};
			vertices[vertices.size() - 3].texCoords = {0 + static_cast<float>(texture.getSize().x), 0};
			vertices[vertices.size() - 2].texCoords = {0 + static_cast<float>(texture.getSize().x), 0 + static_cast<float>(texture.getSize().y)};
			vertices[vertices.size() - 1].texCoords = {0, 0 + static_cast<float>(texture.getSize().y)};
		}
		
		return {this, verts};
	}
	
	sf::Vector2u SpriteBatch::getTextureSize() const
	{
		return texture.getSize();
	}
	
	sf::Vertex* SpriteBatch::getVertex(std::size_t i)
	{
		if(i < vertices.size())
			return &vertices[i];
		else
			return nullptr;
	}
	
	void SpriteBatch::remove(const std::array<std::size_t, 4>& verts)
	{
		vertices.erase(vertices.begin() + verts[0], vertices.begin() + verts[3]);
	}

	void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = &texture;
		target.draw(vertices.data(), vertices.size(), sf::Quads, states);
	}
}
