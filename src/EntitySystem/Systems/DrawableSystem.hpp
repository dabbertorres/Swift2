#ifndef DRAWABLESYSTEM_HPP
#define DRAWABLESYSTEM_HPP

#include "../System.hpp"

#include "../Entity.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace swift
{
	class DrawableSystem : public System
	{
		public:
			virtual void update(const std::vector<Entity*>& entities, float dt);
			
			virtual void draw(const std::vector<Entity*>& entities, sf::RenderTarget& target, sf::RenderStates states) const;
	};
}

#endif // DRAWABLESYSTEM_HPP
