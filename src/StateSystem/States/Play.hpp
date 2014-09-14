#ifndef PLAY_HPP
#define PLAY_HPP

#include "../State.hpp"

/* GUI headers */
#include "../../GUI/Window.hpp"

/* Entity System */
#include "../../EntitySystem/Entity.hpp"

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
			
			Entity entity;
	};
}

#endif // PLAY_HPP
