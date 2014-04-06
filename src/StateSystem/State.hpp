#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/* Input headers */
#include "../KeyBindings/KeyboardManager.hpp"
#include "../KeyBindings/MouseManager.hpp"

/* GUI headers */
#include "../GUI/Window.hpp"
#include "../GUI/Widgets.hpp"

namespace swift
{
	class State
	{
		public:
			State(sf::RenderWindow& win);
			~State();
			
			virtual void handleEvents() = 0;
			virtual void update() = 0;
			virtual void draw(float i) = 0;

		private:
			sf::RenderWindow& window;
	};
}

#endif // STATE_HPP
