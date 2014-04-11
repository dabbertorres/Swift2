#include "Collidable.hpp"

namespace swift
{
	Collidable::Collidable(const sf::Sprite& sprite, unsigned t)
		:	Component(), 
			bounds(sprite.getGlobalBounds())
	{
		sf::Vector2f center = {bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f};
		radius = std::sqrt((bounds.left + center.x) * (bounds.left + center.x) +
		                   (bounds.top + center.y) * (bounds.top + center.y));

		makeBitmask(*sprite.getTexture(), t);
	}

	Collidable::~Collidable()
	{
	}

	bool Collidable::collision(const Collidable& one, const Collidable& two)
	{
		// circle collision test
		sf::Vector2f distance = one.getPosition() - two.getPosition();
		if((distance.x * distance.x) + (distance.y * distance.y) <= (one.getRadius() + one.getRadius()) * (two.getRadius() * two.getRadius()))
		{
			// rectangle test
			sf::FloatRect intersection;
			if(one.getBounds().intersects(two.getBounds(), intersection))
			{				
				// pixel perfect test
				for(int i = intersection.top; i < intersection.top + intersection.height; i++)
				{
					for(int j = intersection.left; j < intersection.left + intersection.width; j++)
					{
						// normalize (0, 0) to collision, and check if both bitmasks are true at that position
						if(	one.getBitmask()[(i - one.getPosition().x) * one.getBounds().width + (j - one.getPosition().y)] && 
							two.getBitmask()[(i - two.getPosition().x) * two.getBounds().width + (j - two.getPosition().y)])
							return true;
					}
				}
			}
		}

		return false;
	}

	sf::Vector2f Collidable::getPosition() const
	{
		return {bounds.left, bounds.top};
	}

	sf::FloatRect Collidable::getBounds() const
	{
		return bounds;
	}

	float Collidable::getRadius() const
	{
		return radius;
	}

	const Bitmask& Collidable::getBitmask() const
	{
		return bitmask;
	}

	void Collidable::makeBitmask(const sf::Texture& texture, unsigned threshold = 128)
	{
		sf::Image image = texture.copyToImage();

		// reserve memory for the bitmask
		bitmask.resize(image.getSize().x * image.getSize().y);

		// calculate and fill the bitmask
		for(unsigned i = 0; i < image.getSize().y; i++)
		{
			for(unsigned j = 0; i < image.getSize().x; j++)
			{
				bitmask[i * image.getSize().x + j] = image.getPixel(j, i).a >= threshold;
			}
		}
	}
}
