#include "Collision.hpp"

#include "../EntitySystem/Systems/MovableSystem.hpp"

#include "../EntitySystem/Components/Physical.hpp"

#include "../World/World.hpp"

#include "../Math/Math.hpp"

#include "Projection.hpp"

namespace swift
{
	const MovableSystem* Collision::movables = nullptr;
	
	Collision::Collision(Physical& o, Physical& t)
	:	one(o),
		two(t),
		idOne(o.ID()),
		idTwo(t.ID()),
		position({-1.f, -1.f}),
		result(false)
	{
		result = handle();
	}

	unsigned int Collision::getFirstID() const
	{
		return idOne;
	}
	
	unsigned int Collision::getSecondID() const
	{
		return idTwo;
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
		// make sure we're actually dealing with collidable entities
		if(!(one.collides && two.collides))
			return false;
		
		// make sure the entites are in the same plane
		if(one.zIndex != two.zIndex)
			return false;
		
		// make sure at least one of the entities is able to move
		if(!(movables->has(idOne) || movables->has(idTwo)))
			return false;
		
		return separatingAxisTheorem();
	}
	
	bool Collision::circularCollision()
	{
		// get the center points of the entities
		sf::Vector2f centerPosOne = one.position + static_cast<sf::Vector2f>(one.size) / 2.f;
		sf::Vector2f centerPosTwo = two.position + static_cast<sf::Vector2f>(two.size) / 2.f;
		
		// radius of the circle is half of the diagonal of the rectangle
		float radiusOne = std::sqrt(one.size.x * one.size.x + one.size.y * one.size.y) / 2.f;
		float radiusTwo = std::sqrt(two.size.x * two.size.x + two.size.y * two.size.y) / 2.f;
		
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
		one.position = newCenterPosOne - static_cast<sf::Vector2f>(one.size) / 2.f;
		two.position = newCenterPosTwo - static_cast<sf::Vector2f>(two.size) / 2.f;
		
		return true;
	}
	
	bool Collision::separatingAxisTheorem()
	{
		// get length of diagonals
		float oneDiagLength = std::sqrt(one.size.x * one.size.x + one.size.y * one.size.y);
		float oneDiagAngle = std::atan2(one.size.y, one.size.x) * 180.f / math::PI;
		float twoDiagLength = std::sqrt(two.size.x * two.size.x + two.size.y * two.size.y);
		float twoDiagAngle = std::atan2(two.size.y, two.size.x) * 180.f / math::PI;
		
		// points of the rects clockwise
		sf::Vector2f oneVerts[4];
		oneVerts[0] = one.position;
		oneVerts[1] = one.position + sf::Vector2f(one.size.x * std::cos(one.angle * math::PI / 180.f), one.size.x * std::sin(one.angle * math::PI / 180.f));
		oneVerts[2] = one.position + sf::Vector2f(oneDiagLength * std::cos((one.angle + oneDiagAngle) * math::PI / 180.f), oneDiagLength * std::sin((one.angle + oneDiagAngle) * math::PI / 180.f));
		oneVerts[3] = one.position + sf::Vector2f(one.size.y * std::cos((one.angle + 90.f) * math::PI / 180.f), one.size.y * std::sin((one.angle + 90.f) * math::PI / 180.f));
		
		sf::Vector2f twoVerts[4];
		twoVerts[0] = two.position;
		twoVerts[1] = two.position + sf::Vector2f(two.size.x * std::cos(two.angle * math::PI / 180.f), two.size.x * std::sin(two.angle * math::PI / 180.f));
		twoVerts[2] = two.position + sf::Vector2f(twoDiagLength * std::cos((two.angle + twoDiagAngle) * math::PI / 180.f), twoDiagLength * std::sin((two.angle + twoDiagAngle) * math::PI / 180.f));
		twoVerts[3] = two.position + sf::Vector2f(two.size.y * std::cos((two.angle + 90.f) * math::PI / 180.f), two.size.y * std::sin((two.angle + 90.f) * math::PI / 180.f));
		
		// axes to test from rect 1
		sf::Vector2f oneAxes[4];
		oneAxes[0] = math::normalY(oneVerts[1] - oneVerts[0]);
		oneAxes[1] = math::normalY(oneVerts[2] - oneVerts[1]);
		oneAxes[2] = math::normalY(oneVerts[3] - oneVerts[2]);
		oneAxes[3] = math::normalY(oneVerts[0] - oneVerts[3]);
		
		// axes to test from rect 2
		sf::Vector2f twoAxes[4];
		twoAxes[0] = math::normalY(twoVerts[1] - twoVerts[0]);
		twoAxes[1] = math::normalY(twoVerts[2] - twoVerts[1]);
		twoAxes[2] = math::normalY(twoVerts[3] - twoVerts[2]);
		twoAxes[3] = math::normalY(twoVerts[0] - twoVerts[3]);
		
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
		if(movables->has(idOne) && movables->has(idTwo))
		{
			one.position -= smallestAxis * (overlap / 2.f);
			two.position += smallestAxis * (overlap / 2.f);
		}
		// only one is a movable
		else
		{
			Physical& movable = movables->has(idOne) ? one : two;
			
			movable.position -= (smallestAxis * overlap);
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
