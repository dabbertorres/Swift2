#include "TileMap.hpp"

#include <sstream>
#include <fstream>

#include <tinyxml2.h>

#include "../Logger/Logger.hpp"

namespace swift
{
	TileMap::TileMap()
	:	tileSize({0, 0}),
		sizePixels({0, 0}),
		sizeTiles({0, 0}),
		textureSize({0, 0}),
		textureTileSize({0, 0}),
		file(""),
		textureFile(""),
		texture(nullptr)
	{
	}

	TileMap::~TileMap()
	{
		texture = nullptr;
	}
	
	void TileMap::update(float dt)
	{
		for(auto& l : layers)
		{
			l.update(dt);
		}
	}

	bool TileMap::loadFile(const std::string& f)
	{
		file = f;
		
		tinyxml2::XMLDocument loadFile;
		loadFile.LoadFile(f.c_str());

		if(loadFile.Error())
		{
			log << "[ERROR] Loading world save file \"" << f << "\" failed.\n";
			return false;
		}

		tinyxml2::XMLElement* mapRoot = loadFile.FirstChildElement("map");
		if(mapRoot == nullptr)
		{
			log << "[WARNING] World save file \"" << f << "\" does not have a \"map\" root element.\n";
			return false;
		}

		sizeTiles.x = std::stoi(mapRoot->Attribute("width"));
		sizeTiles.y = std::stoi(mapRoot->Attribute("height"));
		tileSize.x = std::stoi(mapRoot->Attribute("tilewidth"));
		tileSize.y = std::stoi(mapRoot->Attribute("tileheight"));
		sizePixels.x = sizeTiles.x * tileSize.x;
		sizePixels.y = sizeTiles.y * tileSize.y;

		tinyxml2::XMLElement* tileset = mapRoot->FirstChildElement("tileset");
		textureTileSize.x = std::stoi(tileset->Attribute("tilewidth"));
		textureTileSize.y = std::stoi(tileset->Attribute("tileheight"));

		tinyxml2::XMLElement* image = tileset->FirstChildElement("image");
		textureFile = image->Attribute("source");
		textureSize.x = std::stoi(image->Attribute("width"));
		textureSize.y = std::stoi(image->Attribute("height"));

		tinyxml2::XMLElement* tileType = tileset->FirstChildElement("tile");
		while(tileType != nullptr)
		{
			unsigned int id = std::stoi(tileType->Attribute("id"));
			tileTypes.emplace(id, TileType());
			TileType& current = tileTypes[id];

			current.texPos.x = (id % (textureSize.x / textureTileSize.x)) * textureTileSize.x;
			current.texPos.y = (id / (textureSize.x / textureTileSize.x)) * textureTileSize.y;

			tinyxml2::XMLElement* properties = tileType->FirstChildElement("properties");
			tinyxml2::XMLElement* property = properties->FirstChildElement("property");
			while(property != nullptr)
			{
				if(property->Attribute("name", "Passable"))
				{
					current.passable = property->Attribute("value", "1") ? true : false;
				}
				else if(property->Attribute("name", "Animated"))
				{
					current.animated = property->Attribute("value", "1") ? true : false;
				}

				property = property->NextSiblingElement("property");
			}

			tileType = tileType->NextSiblingElement("tile");
		}

		tinyxml2::XMLElement* layer = mapRoot->FirstChildElement("layer");
		while(layer != nullptr)
		{
			layers.emplace_back(sizeTiles, tileSize);

			tinyxml2::XMLElement* data = layer->FirstChildElement("data");
			std::string mapTiles = data->GetText();
			std::istringstream iss(mapTiles);
			std::string tileNum;
			
			while(std::getline(iss, tileNum, ','))
			{
				int gid = std::stoi(tileNum) - 1;	// Tiled stores gids as tileset # + id in a tileset since I'm just using 1 tileset... "- 1" makes it easy
				
				if(gid != -1)
					layers.back().addTile(tileTypes[gid].texPos, textureTileSize, tileTypes[gid].passable, gid);
				else	// if no tile goes here
					layers.back().addTile({0, 0}, {0, 0}, true, -1);
			}

			layer = layer->NextSiblingElement("layer");
		}

		return true;
	}

	bool TileMap::loadTexture(const sf::Texture& tex)
	{
		texture = &tex;
		if(!texture)
			return false;

		sf::Vector2f scale = {static_cast<float>(tileSize.x) / textureTileSize.x, static_cast<float>(tileSize.y) / textureTileSize.y};

		for(auto& l : layers)
		{
			for(unsigned i = 0; i < sizeTiles.x; i++)
			{
				for(unsigned j = 0; j < sizeTiles.y; j++)
				{
					if(i + j * sizeTiles.x >= l.getNumTiles())
						return false;

					// pointer to quad
					sf::Vertex* quad = &l.vertices[(i + j * sizeTiles.x) * 4];

					// current tile number
					int tileNum = l.getTile(i + j * sizeTiles.x)->getID();
					
					// if no tile should be displayed here, make it transparent
					if(tileNum == -1)
					{
						quad[0].color = {0, 0, 0, 0};
						quad[1].color = {0, 0, 0, 0};
						quad[2].color = {0, 0, 0, 0};
						quad[3].color = {0, 0, 0, 0};
					}
					
					// define 4 corners
					quad[0].position = {std::floor(i * static_cast<float>(tileSize.x) * scale.x), std::floor(j * static_cast<float>(tileSize.y) * scale.y)};
					quad[1].position = {std::floor((i + 1) * static_cast<float>(tileSize.x) * scale.x), std::floor(j * static_cast<float>(tileSize.y) * scale.y)};
					quad[2].position = {std::floor((i + 1) * static_cast<float>(tileSize.x) * scale.x), std::floor((j + 1) * static_cast<float>(tileSize.y) * scale.y)};
					quad[3].position = {std::floor(i * static_cast<float>(tileSize.x) * scale.x), std::floor((j + 1) * static_cast<float>(tileSize.y) * scale.y)};

					// define 4 tex coordinates
					quad[0].texCoords = {static_cast<float>(tileTypes[tileNum].texPos.x), static_cast<float>(tileTypes[tileNum].texPos.y)};
					quad[1].texCoords = {static_cast<float>(tileTypes[tileNum].texPos.x + tileSize.x), static_cast<float>(tileTypes[tileNum].texPos.y)};
					quad[2].texCoords = {static_cast<float>(tileTypes[tileNum].texPos.x + tileSize.x), static_cast<float>(tileTypes[tileNum].texPos.y + tileSize.y)};
					quad[3].texCoords = {static_cast<float>(tileTypes[tileNum].texPos.x), static_cast<float>(tileTypes[tileNum].texPos.y + tileSize.y)};
				}
			}
		}

		return true;
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

	const Tile* TileMap::getTile(unsigned int t, unsigned int l) const
	{
		if(l < layers.size() && t < layers[l].getNumTiles())
			return layers[l].getTile(t);
		else
			return nullptr;
	}

	const Tile* TileMap::getTile(const sf::Vector2f& pos, unsigned int l) const
	{
		if(l < layers.size())
			return layers[l].getTile(pos);
		else
			return nullptr;
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
	
	const std::string& TileMap::getFile() const
	{
		return file;
	}

	unsigned int TileMap::getNumOfTileTypes() const
	{
		return tileTypes.size();
	}

	void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = texture;

		for(auto& l : layers)
		{
			target.draw(l, states);
		}
	}
}
