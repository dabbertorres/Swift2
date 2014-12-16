#include "Layer.hpp"

namespace swift
{
	Layer::Layer(const sf::Vector2u& s, const sf::Vector2u& ts)
	:	vertices(sf::PrimitiveType::Quads),
		size(s),
		tileSize(ts)
	{
		vertices.resize(size.x * size.y * 4);
	}

	Layer::~Layer()
	{
	}
	
	void Layer::update(float dt)
	{
		for(auto& t : tiles)
		{
			t.update(dt);
		}
	}
			
	void Layer::setPosition(const sf::Vector2f& pos)
	{
		
	}
	
	void Layer::addTile(const sf::Vector2u& texPos, const sf::Vector2u& texSize, bool p, unsigned int i)
	{
		tiles.emplace_back(texPos, texSize, p, i);
	}
	
	unsigned int Layer::getNumTiles() const
	{
		return tiles.size();
	}
	
	Tile* Layer::getTile(unsigned int t)
	{
		if(t < tiles.size())
			return &tiles[t];
		else
			return nullptr;
	}
	
	Tile* Layer::getTile(const sf::Vector2f& pos)
	{
		unsigned int tileNum = pos.x + pos.y * size.x;
		if(tileNum < tiles.size())
			return &tiles[tileNum];
		else
			return nullptr;
	}
	
	void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(vertices, states);
	}
}
