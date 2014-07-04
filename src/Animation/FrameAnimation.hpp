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
	class FrameAnimation : public sf::Drawable
	{
		public:
			FrameAnimation();
			~FrameAnimation();
			
			void update(float dt);
			void setFrame(unsigned fn);
			
			sf::FloatRect getGlobalBounds() const;
			
			void setTexture(const sf::Texture& tex);
			void setTime(float seconds);
			void setPosition(sf::Vector2f pos);
			void setLooping(bool l);
			void setRotation(float a);
			void setOrigin(sf::Vector2f o);
			void setScale(sf::Vector2f s);
			
			void addFrame(sf::IntRect rect);

		private:
			void nextFrame();
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			sf::Sprite sprite;

			std::vector<sf::IntRect> frames;
			unsigned frameNum;
			
			float totalTime;	// time the animation lasts
			float currentTime;	// current time in animation
			
			bool looping;
			bool done;	// set to true if animation is non-looping and is done
	};
}

#endif // FRAMEANIMATION_HPP
