#ifndef DRAWABLESYSTEM_HPP
#define DRAWABLESYSTEM_HPP

#include "../System.hpp"

#include "../Components/Drawable.hpp"
#include "../Components/Physical.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace swift
{
	class DrawableSystem : public System<Drawable>
	{
		public:
			DrawableSystem();

			virtual void update(float dt);

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			void setPhysSystem(System<Physical>* ps);

		private:
			System<Physical>* physSystem;
	};
}

#endif // DRAWABLESYSTEM_HPP
