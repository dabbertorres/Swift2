#include "FrameAnimation.hpp"

namespace swift
{
	FrameAnimation::FrameAnimation()
	{
		totalTime = 0;
		currentTime = 0;
		frameNum = 0;
		looping = true;
		done = false;
	}

	FrameAnimation::~FrameAnimation()
	{
	}

	void FrameAnimation::update(float dt)
	{
		currentTime += dt;

		if(dt >= totalTime / frames.size() && (currentTime < totalTime || looping))
			nextFrame();

		if(!looping && currentTime >= totalTime)
			done = true;
	}
	
	sf::FloatRect FrameAnimation::getGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}
	
	void FrameAnimation::setTexture(const sf::Texture& tex)
	{
		sprite.setTexture(tex);
	}

	void FrameAnimation::setTime(float seconds)
	{
		totalTime = seconds;
	}

	void FrameAnimation::setPosition(sf::Vector2f pos)
	{
		sprite.setPosition(pos);
	}
	
	void FrameAnimation::setLooping(bool l)
	{
		looping = l;
	}
	
	void FrameAnimation::setRotation(float a)
	{
		sprite.setRotation(a);
	}
	
	void FrameAnimation::setOrigin(sf::Vector2f o)
	{
		sprite.setOrigin(o);
	}
	
	void FrameAnimation::setScale(sf::Vector2f s)
	{
		sprite.setScale(s);
	}

	void FrameAnimation::addFrame(sf::IntRect rect)
	{
		frames.push_back(rect);
	}

	void FrameAnimation::nextFrame()
	{
		if(frames.size() > 0)
		{
			frameNum >= frames.size() ? frameNum = 0 : frameNum++;
			sprite.setTextureRect(frames[frameNum]);
		}
	}

	void FrameAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}
}
