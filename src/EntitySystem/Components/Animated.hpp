#ifndef ANIMATED_HPP
#define ANIMATED_HPP

#include "../Component.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include "../../Animation/AnimTexture.hpp"
#include "../../Animation/FrameAnimation.hpp"

namespace swift
{
	class Animated : public Component
	{
		public:
			Animated();
			
			void setAnimation(const std::string& anim);
			void revertAnimation();
			bool createAnimations();
			
			static std::string getType();
			
			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);

			sf::Sprite sprite;
			AnimTexture* animTex;
			std::map<std::string, FrameAnimation> anims;
			std::string currentAnim;
			std::string previousAnim;
			std::string animationFile;
	};
}

#endif // ANIMATED_HPP
