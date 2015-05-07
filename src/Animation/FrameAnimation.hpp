#ifndef FRAMEANIMATION_HPP
#define FRAMEANIMATION_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <vector>

namespace swift
{
	class FrameAnimation
	{
		public:
			FrameAnimation();
			
			const sf::IntRect& update(float dt);
			
			void play();
			void stop();
			
			void setFrameNum(unsigned int fn);
			void addFrame(const sf::IntRect& rect);
			void setFrames(const std::vector<sf::IntRect>& fs);
			
			void setTime(float seconds);
			void setLooping(bool l);
			
			bool isPlaying() const;

		private:
			std::vector<sf::IntRect> frames;
			unsigned int frameNum;
			
			float totalTime;	// time the animation lasts
			float currentTime;	// current time in animation
			
			bool looping;
			bool done;	// set to true if animation is non-looping and is done
			bool playing;
	};
}

#endif // FRAMEANIMATION_HPP
