#ifndef ANIMATEDSYSTEM_HPP
#define ANIMATEDSYSTEM_HPP

#include "../System.hpp"

#include "../Entity.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace swift
{
	class AnimatedSystem : public System
	{
		public:
			virtual void update(const std::vector<Entity>& entities, float dt);
			
			virtual void draw(const std::vector<Entity>& entities, float e, sf::RenderTarget& target, sf::RenderStates states) const;
	};
}

#endif // ANIMATEDSYSTEM_HPP
