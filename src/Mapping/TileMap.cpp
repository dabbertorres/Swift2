#include "TileMap.hpp"

#include <sstream>
#include <fstream>

namespace swift
{
	TileMap::TileMap()
		:	tileSize({0, 0}),
			sizePixels({0, 0}),
			sizeTiles({0, 0}),
			textureFile(""),
			position({0, 0}),
			vertices(sf::Quads),
			texture(nullptr)
	{
	}

	TileMap::~TileMap()
	{
		texture = nullptr;
	}
	
	bool TileMap::loadFile(const std::string& f)
	{
		std::ifstream fin;
		fin.open(f);
		
		if(fin.bad())
			return false;
		
		unsigned height = 0;
		
		std::string line = "";
		while(std::getline(fin, line))
		{
			if(line.find("texture") != std::string::npos)
			{
				textureFile = line.substr(line.find_first_of('\"') + 1, line.find_last_of('\"') - line.find_first_of('\"') - 1);
			}
			else if(line.find("size") != std::string::npos)
			{
				std::stringstream ss;
				ss << line.substr(line.find('=') + 1);
				ss >> tileSize.x >> tileSize.y;
			}
			else if(line.find('=') != std::string::npos)
			{
				std::stringstream ss;
				ss << line.substr(line.find('=') + 1);
				sf::Vector2u tilePos;
				ss >> tilePos.x >> tilePos.y;
				tileTypes.emplace_back(tilePos);
			}
			else
			{
				std::stringstream ss;
				ss << line;
				int tile = 0;
				
				height++;
				
				unsigned width = 0;
				while(ss >> tile)
				{
					tiles.push_back(tile);
					width++;
				}
				
				sizeTiles.x = width;
			}
		}
		
		sizeTiles.y = height;
		
		return true;
	}
	
	bool TileMap::loadTexture(const sf::Texture& tex)
	{
		texture = &tex;
		vertices.resize(sizeTiles.x * sizeTiles.y * 4);
		
		sf::Vector2f scale = {sizePixels.x / static_cast<float>(sizeTiles.x) / static_cast<float>(tileSize.x), sizePixels.y / static_cast<float>(sizeTiles.y) / static_cast<float>(tileSize.y)};
		
		for(unsigned i = 0; i < sizeTiles.x; i++)
		{
			for(unsigned j = 0; j < sizeTiles.y; j++)
			{
				if(i + j * sizeTiles.x >= tiles.size())
					return false;
				
				// current tile number
				int tileNum = tiles[i + j * sizeTiles.x];
				
				// pointer to quad
				sf::Vertex* quad = &vertices[(i + j * sizeTiles.x) * 4];
				
				// define 4 corners
				quad[0].position = {std::floor(i * static_cast<float>(tileSize.x) * scale.x), std::floor(j * static_cast<float>(tileSize.y) * scale.y)};
				quad[1].position = {std::floor((i + 1) * static_cast<float>(tileSize.x) * scale.x), std::floor(j * static_cast<float>(tileSize.y) * scale.y)};
				quad[2].position = {std::floor((i + 1) * static_cast<float>(tileSize.x) * scale.x), std::floor((j + 1) * static_cast<float>(tileSize.y) * scale.y)};
				quad[3].position = {std::floor(i * static_cast<float>(tileSize.x) * scale.x), std::floor((j + 1) * static_cast<float>(tileSize.y) * scale.y)};
				
				// define 4 tex coordinates
				quad[0].texCoords = {static_cast<float>(tileTypes[tileNum].pos.x), static_cast<float>(tileTypes[tileNum].pos.y)};
				quad[1].texCoords = {static_cast<float>(tileTypes[tileNum].pos.x + tileSize.x), static_cast<float>(tileTypes[tileNum].pos.y)};
				quad[2].texCoords = {static_cast<float>(tileTypes[tileNum].pos.x + tileSize.x), static_cast<float>(tileTypes[tileNum].pos.y + tileSize.y)};
				quad[3].texCoords = {static_cast<float>(tileTypes[tileNum].pos.x), tileTypes[tileNum].pos.y + static_cast<float>(tileSize.y)};
			}
		}
		
		return true;
	}
	
	bool TileMap::saveFile(const std::string& f)
	{
		std::ofstream fout;
		fout.open(f);
		
		if(fout.bad())
			return false;
			
		fout << "texture = \"" << textureFile << "\"\n";
		fout << "size = " << tileSize.x << ' ' << tileSize.y << '\n';
		
		for(auto t = 0u; t < tileTypes.size(); t++)
		{
			fout << t << " = " << tileTypes[t].pos.x << ' ' << tileTypes[t].pos.y << '\n';
		}
		
		for(auto i = 0u; i < sizeTiles.y; i++)
		{
			for(auto j = 0u; j < sizeTiles.x; j++)
			{
				fout << tiles[j + i * sizeTiles.x] << ' ';
			}
			
			fout << '\n';
		}
		
		return true;
	}
	
	void TileMap::setPosition(const sf::Vector2i& pos)
	{
		for(unsigned i = 0; i < sizeTiles.x; i++)
		{
			for(unsigned j = 0; j < sizeTiles.y; j++)
			{
				sf::Vertex* quad = &vertices[(i + j * sizeTiles.x) * 4];
				quad[0].position = static_cast<sf::Vector2f>(pos + static_cast<sf::Vector2i>(quad[0].position) - position);
				quad[1].position = static_cast<sf::Vector2f>(pos + static_cast<sf::Vector2i>(quad[1].position) - position);
				quad[2].position = static_cast<sf::Vector2f>(pos + static_cast<sf::Vector2i>(quad[2].position) - position);
				quad[3].position = static_cast<sf::Vector2f>(pos + static_cast<sf::Vector2i>(quad[3].position) - position);
			}
		}
		
		position = pos;
	}
	
	void TileMap::setTileNum(unsigned t, int n)
	{
		if(t < tiles.size() && static_cast<unsigned>(n) < tileTypes.size())
		{
			tiles[t] = n;
			
			sf::Vertex* quad = &vertices[t * 4];
			quad[0].texCoords = {static_cast<float>(tileTypes[n].pos.x), static_cast<float>(tileTypes[n].pos.y)};
			quad[1].texCoords = {static_cast<float>(tileTypes[n].pos.x + tileSize.x), static_cast<float>(tileTypes[n].pos.y)};
			quad[2].texCoords = {static_cast<float>(tileTypes[n].pos.x + tileSize.x), static_cast<float>(tileTypes[n].pos.y + tileSize.y)};
			quad[3].texCoords = {static_cast<float>(tileTypes[n].pos.x), static_cast<float>(tileTypes[n].pos.y + tileSize.y)};
		}
	}
	
	void TileMap::setTileSize(const sf::Vector2u& ts)
	{
		tileSize = ts;
	}
	
	void TileMap::setSize(const sf::Vector2u& s)
	{
		sizeTiles = s;
	}

	void TileMap::setTextureFile(const std::string& str)
	{
		textureFile = str;
	}
	
	int TileMap::getTileNum(unsigned t) const
	{
		if(t < tiles.size())
			return tiles[t];
		else
			return -1;
	}
	
	const sf::Vector2u& TileMap::getTileSize() const
	{
		return tileSize;
	}
	
	const sf::Vector2u& TileMap::getSize() const
	{
		return sizeTiles;
	}
	
	const std::string& TileMap::getTextureFile() const
	{
		return textureFile;
	}
	
	void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = texture;
		target.draw(vertices, states);
	}
}
