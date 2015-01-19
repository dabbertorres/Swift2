#include "FrameAnimation.hpp"

namespace swift
{
	FrameAnimation::FrameAnimation()
	:	frameNum(0),
	    totalTime(0),
	    currentTime(0),
	    looping(false),
	    done(false)
	{}

	const sf::IntRect& FrameAnimation::update(float dt)
	{
		currentTime += dt;

		if(currentTime >= (totalTime / frames.size()) * (frameNum + 1) && (currentTime < totalTime || looping))
		{
			if(frames.size() > 0 && !done)
			{
				if(frameNum < frames.size() - 1)
				{
					frameNum++;
				}
				else
				{
					frameNum = 0;
					currentTime = 0;
				}
			}
		}

		if(!looping && currentTime >= totalTime)
			done = true;

		return frames[frameNum];
	}

	void FrameAnimation::setFrameNum(unsigned fn)
	{
		if(fn < frames.size())
		{
			frameNum = fn;
		}
	}

	void FrameAnimation::addFrame(const sf::IntRect& rect)
	{
		frames.push_back(rect);
	}

	void FrameAnimation::setFrames(const std::vector<sf::IntRect>& fs)
	{
		frames = fs;
	}

	void FrameAnimation::setTime(float seconds)
	{
		totalTime = seconds;
	}

	void FrameAnimation::setLooping(bool l)
	{
		looping = l;
	}
}
