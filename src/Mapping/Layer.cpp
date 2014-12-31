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
	
	void Layer::update(float dt)
	{
		for(auto& t : tiles)
		{
			t.update(dt);
		}
	}
	
	void Layer::addTile(const sf::Vector2u& texPos, const sf::Vector2u& texSize, bool p, unsigned int z, unsigned int i)
	{
		tiles.emplace_back(texPos, texSize, p, z, i);
	}
	
	unsigned int Layer::getNumTiles() const
	{
		return tiles.size();
	}
	
	const Tile* Layer::getTile(unsigned int t) const
	{
		if(t < tiles.size())
			return &tiles[t];
		else
			return nullptr;
	}
	
	const Tile* Layer::getTile(const sf::Vector2f& pos) const
	{
		unsigned int tileNum = static_cast<unsigned int>(pos.x / tileSize.x) + static_cast<unsigned int>(pos.y / tileSize.y) * size.x;
		return getTile(tileNum);
	}
	
	void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(vertices, states);
	}
}
