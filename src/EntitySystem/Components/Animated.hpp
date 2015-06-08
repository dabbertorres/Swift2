#ifndef ANIMATED_HPP
#define ANIMATED_HPP

#include "../Component.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include "../../Animation/AnimTexture.hpp"
#include "../../Animation/FrameAnimation.hpp"

namespace swift
{
	class Physical;
	
	class Animated : public Component
	{
		public:
			Animated(unsigned int id, const Physical& p);
			
			Animated(const Animated& other);
			
			Animated& operator=(Animated&& other);

			void setAnimation(const std::string& anim);
			void revertAnimation();
			bool createAnimations();
			
			const Physical& getPhysical() const;

			static constexpr Component::Type type();

			virtual std::map<std::string, std::string> serialize() const;
			virtual void unserialize(const std::map<std::string, std::string>& variables);

			sf::Sprite sprite;
			AnimTexture* animTex;
			std::map<std::string, FrameAnimation> anims;
			std::string currentAnim;
			std::string previousAnim;
			std::string animationFile;

		private:
			const Physical& physical;
	};

	constexpr Component::Type Animated::type()
	{
		return Component::Type::Animated;
	}
}

#endif // ANIMATED_HPP
