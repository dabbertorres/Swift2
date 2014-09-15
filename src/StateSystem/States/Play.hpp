#ifndef PLAY_HPP
#define PLAY_HPP

#include "../State.hpp"

#include <vector>

/* GUI headers */
#include "../../GUI/Window.hpp"

/* Entity */
#include "../../EntitySystem/Entity.hpp"

/* Systems */
#include "../../EntitySystem/Systems/DrawableSystem.hpp"
#include "../../EntitySystem/Systems/MovableSystem.hpp"
#include "../../EntitySystem/Systems/PhysicalSystem.hpp"

namespace swift
{
	class Play : public State
	{
		public:
			Play(sf::RenderWindow& win, AssetManager& am);
			~Play();

			virtual void setup();
			virtual void handleEvent(sf::Event& event);
			virtual void update(sf::Time dt);
			virtual void draw(float e);
			virtual bool switchFrom();
			virtual Type finish();

		private:
			// sub state system
			enum class SubState
			{
				Play,
				Pause
			};
			
			void setupKeyBindings();

			cstr::Window hud;
			cstr::Window pauseMenu;
			
			SubState state;
			
			DrawableSystem drawSystem;
			MovableSystem moveSystem;
			PhysicalSystem physicalSystem;
			
			std::vector<Entity> entities;
	};
}

#endif // PLAY_HPP
