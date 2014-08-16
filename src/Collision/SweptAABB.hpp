#ifndef SWEPT_AABB_HPP
#define SWEPT_AABB_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace swift
{
	struct Box
	{
		Box(sf::FloatRect fr, sf::Vector2f vel)
		{
			fr = box;
			velocity = vel;
		}
		
		sf::FloatRect box;		
		sf::Vector2f velocity;
	};
	
	// returns a value 0..1.
	// 0 = start of frame
	// 1 = end of frame (or no collision)
	inline float sweptAABB(Box b1, Box b2, sf::Vector2f& normal)
	{
		// distance the closest edges of the objects are from each other
		sf::Vector2f invEntry;
		// distance the far edges of the objects are from each other
		sf::Vector2f invExit;
		
		if(b1.velocity.x > 0.0f)
		{
			invEntry.x = b2.box.left - (b1.box.left + b1.box.width);
			invExit.x = (b2.box.left + b2.box.width) - b1.box.left;
		}
		else
		{
			invEntry.x = (b2.box.left + b2.box.width) - b1.box.left;
			invExit.x = b2.box.left - (b1.box.left + b1.box.width);
		}
		
		if(b1.velocity.y > 0.0f)
		{
			invEntry.y = b2.box.top - (b1.box.top + b1.box.height);
			invExit.y = (b2.box.top + b2.box.height) - b1.box.top;
		}
		else
		{
			invEntry.y = (b2.box.top + b2.box.height) - b1.box.top;
			invExit.y = b2.box.top - (b1.box.top + b1.box.height);
		}
		
		// find time of collision and time of leaving for each axis
		sf::Vector2f entry;
		sf::Vector2f exit;
		
		if(b1.velocity.x == 0.0f)
		{
			entry.x = -std::numeric_limits<float>::infinity();
			exit.x = std::numeric_limits<float>::infinity();
		}
		else
		{
			entry.x = invEntry.x / b1.velocity.x;
			exit.x = invExit.x / b1.velocity.x;
		}
		
		if(b1.velocity.y == 0.0f)
		{
			entry.y = -std::numeric_limits<float>::infinity();
			exit.y = std::numeric_limits<float>::infinity();
		}
		else
		{
			entry.y = invEntry.y / b1.velocity.y;
			exit.y = invExit.y / b1.velocity.y;
		}
		
		// find earliest/latest times of collision
		float entryTime = std::max(entry.x, entry.y);
		float exitTime = std::max(exit.x, exit.y);
		
		// if no collision
		if(entryTime > exitTime || (entry.x < 0.0f && entry.y < 0.0f) || entry.x > 1.0f || entry.y > 1.0f)
		{
			normal.x = 0.0f;
			normal.y = 0.0f;
			return 1.0f;
		}
		// if collision
		else
		{
			if(entry.x > entry.y)
			{
				if(invEntry.x < 0.0f)
				{
					normal.x = 1.0f;
					normal.y = 0.0f;
				}
				else
				{
					normal.x = -1.0f;
					normal.y = 0.0f;
				}
			}
			else
			{
				if(invEntry.y < 0.0f)
				{
					normal.x = 0.0f;
					normal.y = 1.0f;
				}
				else
				{
					normal.x = 0.0f;
					normal.y = -1.0f;
				}
			}
			
			return entryTime;
		}
	}
}

#endif // SWEPT_AABB_HPP