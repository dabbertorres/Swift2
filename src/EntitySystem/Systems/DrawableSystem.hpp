#ifndef DRAWABLESYSTEM_HPP
#define DRAWABLESYSTEM_HPP

#include "../System.hpp"

#include "../Components/Drawable.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace swift
{
	class DrawableSystem : public System<Drawable>
	{
		public:
			virtual void update(float dt);
			
			virtual void draw(float e, sf::RenderTarget& target, sf::RenderStates states) const;
	};
}

#endif // DRAWABLESYSTEM_HPP
