#include "TileMap.hpp"

#include <fstream>

namespace swift
{
	TileMap::TileMap()
	{
		vertices.setPrimitiveType(sf::Quads);
	}

	TileMap::~TileMap()
	{
		
	}
	
	bool TileMap::load(const sf::Texture& tex, sf::Vector2u tileSize, const std::vector<int>& tiles, unsigned width, unsigned height)
	{
		texture = &tex;
		vertices.resize(width * height * 4);
		
		for(unsigned i = 0; i < width; i++)
		{
			for(unsigned j = 0; j < height; j++)
			{
				if(i + j * width >= tiles.size())
					return false;
				
				// current tile number
				int tileNum = tiles[i + j * width];
				
				// find position in texture
				int tu = tileNum % (texture->getSize().x / tileSize.x);
				int tv = tileNum / (texture->getSize().y / tileSize.x);
				
				// pointer to quad
				sf::Vertex* quad = &vertices[(i + j * width) * 4];
				
				// define 4 corners
				quad[0].position = {i * tileSize.x, j * tileSize.y};
				quad[1].position = {(i + 1) * tileSize.x, j * tileSize.y};
				quad[2].position = {(i + 1) * tileSize.x, (j + 1) * tileSize.y};
				quad[3].position = {i * tileSize.x, (j + 1) * tileSize.y};
				
				// define 4 tex coordinates
				quad[0].texCoords = {tu * tileSize.x, tv * tileSize.y};
				quad[1].texCoords = {(tu + 1) * tileSize.x, tv * tileSize.y};
				quad[2].texCoords = {(tu + 1) * tileSize.x, (tv + 1) * tileSize.y};
				quad[3].texCoords = {tu * tileSize.x, (tv + 1) * tileSize.y};
			}
		}
		
		return true;
	}
	
	void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = texture;
		target.draw(vertices, states);
	}
}
