#include "Collision.hpp"

#include "../EntitySystem/Entity.hpp"

#include "../World/World.hpp"

#include "../Math/Math.hpp"

#include "Projection.hpp"

namespace swift
{
	Collision::Collision(Entity& f, Entity& s)
	:	one(f),
		two(s),
		position({-1.f, -1.f}),
		result(false)
	{
		result = handle();
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
	
	bool Collision::getResult() const
	{
		return result;
	}

	bool Collision::handle()
	{
		Physical* physOne = one.get<Physical>();
		Physical* physTwo = two.get<Physical>();
		
		// make sure we're actually dealing with collidable entities
		if(!(physOne->collides && physTwo->collides))
			return false;
		
		// make sure the entites are in the same plane
		if(physOne->zIndex != physTwo->zIndex)
			return false;
		
		// make sure at least one of the entities is able to move
		if(!(one.has<Movable>() || two.has<Movable>()))
			return false;
		
		return separatingAxisTheorem();
	}
	
	bool Collision::circularCollision()
	{
		Physical* physOne = one.get<Physical>();
		Physical* physTwo = two.get<Physical>();
		
		// get the center points of the entities
		sf::Vector2f centerPosOne = physOne->position + static_cast<sf::Vector2f>(physOne->size) / 2.f;
		sf::Vector2f centerPosTwo = physTwo->position + static_cast<sf::Vector2f>(physTwo->size) / 2.f;
		
		// radius of the circle is half of the diagonal of the rectangle
		float radiusOne = std::sqrt(physOne->size.x * physOne->size.x + physOne->size.y * physOne->size.y) / 2.f;
		float radiusTwo = std::sqrt(physTwo->size.x * physTwo->size.x + physTwo->size.y * physTwo->size.y) / 2.f;
		
		float distanceSqd = math::distanceSquared(centerPosOne, centerPosTwo);
		
		// circle test
		if((radiusOne + radiusTwo) * (radiusOne + radiusTwo) < distanceSqd)
			return false;
		
		// now handle the collision
		float depth = radiusOne + radiusTwo - std::sqrt(distanceSqd);
		float halfDepth = depth / 2.f;	// each circle went half of depth into the other circle
		
		// midpoint of 2 vectors formula
		sf::Vector2f position = centerPosOne + 0.5f * (centerPosTwo - centerPosOne);
		
		sf::Vector2f newCenterPosOne = scaledDiffVector(centerPosOne, position, halfDepth);
		sf::Vector2f newCenterPosTwo = scaledDiffVector(centerPosTwo, position, halfDepth);
		
		// translate from center to top-left
		physOne->position = newCenterPosOne - static_cast<sf::Vector2f>(physOne->size) / 2.f;
		physTwo->position = newCenterPosTwo - static_cast<sf::Vector2f>(physTwo->size) / 2.f;
		
		return true;
	}
	
	bool Collision::separatingAxisTheorem()
	{
		Physical* physOne = one.get<Physical>();
		Physical* physTwo = two.get<Physical>();
			
		// get length of diagonals
		float oneDiagLength = std::sqrt(physOne->size.x * physOne->size.x + physOne->size.y * physOne->size.y);
		float oneDiagAngle = std::atan2(physOne->size.y, physOne->size.x) * 180.f / math::PI;
		float twoDiagLength = std::sqrt(physTwo->size.x * physTwo->size.x + physTwo->size.y * physTwo->size.y);
		float twoDiagAngle = std::atan2(physTwo->size.y, physTwo->size.x) * 180.f / math::PI;
		
		// points of the rects clockwise
		// -std::sin because of the flipped graphical y-axis
		sf::Vector2f oneVerts[4];
		oneVerts[0] = physOne->position;
		oneVerts[1] = physOne->position + sf::Vector2f(physOne->size.x * std::cos(physOne->angle * math::PI / 180.f), physOne->size.x * std::sin(physOne->angle * math::PI / 180.f));
		oneVerts[2] = physOne->position + sf::Vector2f(oneDiagLength * std::cos((physOne->angle + oneDiagAngle) * math::PI / 180.f), oneDiagLength * std::sin((physOne->angle + oneDiagAngle) * math::PI / 180.f));
		oneVerts[3] = physOne->position + sf::Vector2f(physOne->size.y * std::cos((physOne->angle + 90.f) * math::PI / 180.f), physOne->size.y * std::sin((physOne->angle + 90.f) * math::PI / 180.f));
		
		sf::Vector2f twoVerts[4];
		twoVerts[0] = physTwo->position;
		twoVerts[1] = physTwo->position + sf::Vector2f(physTwo->size.x * std::cos(physTwo->angle * math::PI / 180.f), physTwo->size.x * std::sin(physTwo->angle * math::PI / 180.f));
		twoVerts[2] = physTwo->position + sf::Vector2f(twoDiagLength * std::cos((physTwo->angle + twoDiagAngle) * math::PI / 180.f), twoDiagLength * std::sin((physTwo->angle + twoDiagAngle) * math::PI / 180.f));
		twoVerts[3] = physTwo->position + sf::Vector2f(physTwo->size.y * std::cos((physTwo->angle + 90.f) * math::PI / 180.f), physTwo->size.y * std::sin((physTwo->angle + 90.f) * math::PI / 180.f));
		
		// axes to test from rect 1
		sf::Vector2f oneAxes[4];
		oneAxes[0] = math::normal(oneVerts[1] - oneVerts[0]);
		oneAxes[1] = math::normal(oneVerts[2] - oneVerts[1]);
		oneAxes[2] = math::normal(oneVerts[3] - oneVerts[2]);
		oneAxes[3] = math::normal(oneVerts[0] - oneVerts[3]);
		
		// axes to test from rect 2
		sf::Vector2f twoAxes[4];
		twoAxes[0] = math::normal(twoVerts[1] - twoVerts[0]);
		twoAxes[1] = math::normal(twoVerts[2] - twoVerts[1]);
		twoAxes[2] = math::normal(twoVerts[3] - twoVerts[2]);
		twoAxes[3] = math::normal(twoVerts[0] - twoVerts[3]);
		
		// check for overlap between projections onto axes
		float overlap = -1.f;
		sf::Vector2f smallestAxis;
		for(int i = 0; i < 4; i++)
		{
			Projection<float> p1(oneAxes[i], oneVerts);
			Projection<float> p2(oneAxes[i], twoVerts);
			
			float o = p1.overlap(p2);
			if(o == 0.f)
				return false;
			
			if(overlap < 0.f || o < overlap)
			{
				overlap = o;
				smallestAxis = oneAxes[i];
			}
		}
		
		for(int i = 0; i < 4; i++)
		{
			Projection<float> p1(twoAxes[i], oneVerts);
			Projection<float> p2(twoAxes[i], twoVerts);
			
			float o = p1.overlap(p2);
			if(o == 0.f)
				return false;
			
			if(overlap < 0.f || o < overlap)
			{
				overlap = o;
				smallestAxis = twoAxes[i];
			}
		}
		
		// well, since we're here, they collided. now to handle the collision...
		// if both are movable, move both
		if(one.has<Movable>() && two.has<Movable>())
		{
			one.get<Physical>()->position -= smallestAxis * (overlap / 2.f);
			two.get<Physical>()->position += smallestAxis * (overlap / 2.f);
		}
		// only one is a movable
		else
		{
			Physical* movable = one.has<Movable>() ? one.get<Physical>() : two.get<Physical>();
			Physical* stuck = one.has<Movable>() ? two.get<Physical>() : one.get<Physical>();
			
			movable->position -= (smallestAxis * overlap);
		}
		
		return true;
	}
	
	sf::Vector2f Collision::scaledDiffVector(const sf::Vector2f& oneVec, const sf::Vector2f& twoVec, float wantLength)
	{
		sf::Vector2f twoToOne = twoVec - oneVec;
		float length = std::sqrt(twoToOne.x * twoToOne.x + twoToOne.y * twoToOne.y);
		
		sf::Vector2f unitVec = twoToOne / length;
		
		return oneVec - unitVec * wantLength;
	}
}
