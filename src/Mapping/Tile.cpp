#include "Tile.hpp"

namespace swift
{
	Tile::Tile(const sf::Vector2u& texPos, const sf::Vector2u& texSize, bool p, unsigned int z, unsigned int i)
	:	frameNum(0),
		passable(p),
		animated(false),
		animationTime(0.f),
		currentTime(0.f),
		zIndex(z),
		id(i)
	{
		texRects.push_back({static_cast<int>(texPos.x), static_cast<int>(texPos.y), static_cast<int>(texSize.x), static_cast<int>(texSize.y)});
	}
	
	void Tile::update(float dt)
	{
		if(animated)
		{
			currentTime += dt;
			if(currentTime >= (animationTime / texRects.size()) * (frameNum + 1))
			{
				frameNum++;
				
				if(frameNum >= texRects.size())
					frameNum = 0;
			}
		}
	}
	
	void Tile::addFrame(const sf::IntRect& r)
	{
		texRects.push_back(r);
	}
	
	void Tile::setAnimated(bool a)
	{
		animated = a;
	}
	
	bool Tile::isAnimated() const
	{
		return animated;
	}
	
	void Tile::setAnimationTime(float t)
	{
		animationTime = t;
	}
	
	bool Tile::isPassable() const
	{
		return passable;
	}
	
	unsigned int Tile::getZindex() const
	{
		return zIndex;
	}
	
	unsigned int Tile::getID() const
	{
		return id;
	}
}
