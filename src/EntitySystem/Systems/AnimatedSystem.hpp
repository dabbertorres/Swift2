#ifndef ANIMATEDSYSTEM_HPP
#define ANIMATEDSYSTEM_HPP

#include "../System.hpp"

#include "../Components/Animated.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace swift
{
	class AnimatedSystem : public System<Animated>
	{
		public:
			virtual void update(float dt);
			
			virtual void draw(float e, sf::RenderTarget& target, sf::RenderStates states) const;
	};
}

#endif // ANIMATEDSYSTEM_HPP
