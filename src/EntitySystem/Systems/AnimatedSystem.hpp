#ifndef SWIFT_ANIMATED_SYSTEM_HPP
#define SWIFT_ANIMATED_SYSTEM_HPP

#include "../System.hpp"

#include "../Components/Animated.hpp"
#include "../Components/Physical.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace swift
{
	class AnimatedSystem : public System<Animated>
	{
		public:
			AnimatedSystem();

			virtual void update(float dt);

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			void setPhysSystem(System<Physical>* ps);

		private:
			System<Physical>* physSystem;
	};
}

#endif // ANIMATEDSYSTEM_HPP
