#include "FrameAnimation.hpp"

namespace swift
{
	FrameAnimation::FrameAnimation(const sf::Texture& tex, bool l)
	{
		sprite.setTexture(tex);
		totalTime = 0;
		currentTime = 0;
		frameNum = 0;
		looping = l;
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

	void FrameAnimation::setTime(float seconds)
	{
		totalTime = seconds;
	}

	void FrameAnimation::setPosition(sf::Vector2f pos)
	{
		sprite.setPosition(pos);
	}

	void FrameAnimation::addFrame(sf::IntRect rect)
	{
		frames.push_back(rect);
	}

	void FrameAnimation::nextFrame()
	{
		frameNum >= frames.size() ? frameNum = 0 : frameNum++;
		sprite.setTextureRect(frames[frameNum]);
	}

	void FrameAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}
}
