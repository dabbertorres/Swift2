#include "Collision.hpp"

#include "../EntitySystem/Entity.hpp"

#include "../World/World.hpp"

namespace swift
{
	Collision::Collision(Entity& f, Entity& s)
		:	one(f),
			two(s)
	{
		if(one.has<Physical>() && two.has<Physical>())
		{
			bool result = handle();

			if(result)
				sendMessage("Collision occured", *this);
		}
	}

	Collision::~Collision()
	{
	}

	Entity& Collision::getFirstEntity() const
	{
		return one;
	}
	
	Entity& Collision::getSecondEntity() const
	{
		return two;
	}

	const sf::Vector2f& Collision::getPosition() const
	{
		return position;
	}

	bool Collision::handle()
	{
		if(!one.has<Physical>() || !two.has<Physical>())
			return false;
			
		Physical* physOne = one.get<Physical>();
		Physical* physTwo = two.get<Physical>();
		
		if(!physOne->collides || !physTwo->collides)
			return false;
		
		// get the center points of the entities
		sf::Vector2f centerPosOne = physOne->position + static_cast<sf::Vector2f>(physOne->size) / 2.f;
		sf::Vector2f centerPosTwo = physTwo->position + static_cast<sf::Vector2f>(physTwo->size) / 2.f;
		
		// radius of the circle is half of the diagonal of the rectangle
		float radiusOne = std::sqrt(physOne->size.x * physOne->size.x + physOne->size.y * physOne->size.y) / 2.f;
		float radiusTwo = std::sqrt(physTwo->size.x * physTwo->size.x + physTwo->size.y * physTwo->size.y) / 2.f;
		
		float distanceSqd = World::distanceSquared(centerPosOne, centerPosTwo);
		
		// circle test
		if((radiusOne + radiusTwo) * (radiusOne + radiusTwo) < distanceSqd)
			return false;
		
		float depth = radiusOne + radiusTwo - std::sqrt(distanceSqd);
		float halfDepth = depth / 2;	// each circle went half of depth into the other circle
		
		// midpoint of 2 vectors formula
		sf::Vector2f collisionPoint = centerPosOne + 0.5f * (centerPosTwo - centerPosOne);
		
		sf::Vector2f newCenterPosOne = scaledDiffVector(centerPosOne, collisionPoint, halfDepth);
		sf::Vector2f newCenterPosTwo = scaledDiffVector(centerPosTwo, collisionPoint, halfDepth);
		
		// translate from center to top-left
		physOne->position = newCenterPosOne - static_cast<sf::Vector2f>(physOne->size) / 2.f;
		physTwo->position = newCenterPosTwo - static_cast<sf::Vector2f>(physTwo->size) / 2.f;
		
		return true;
	}
	
	sf::Vector2f Collision::scaledDiffVector(const sf::Vector2f& one, const sf::Vector2f& two, float wantLength)
	{
		sf::Vector2f twoToOne = two - one;
		float length = std::sqrt(twoToOne.x * twoToOne.x + twoToOne.y * twoToOne.y);
		
		sf::Vector2f unitVec = twoToOne / length;
		
		return one - unitVec * wantLength;
	}
}
