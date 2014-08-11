#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/* Input headers */
#include "../KeyBindings/KeyboardManager.hpp"
#include "../KeyBindings/MouseManager.hpp"

namespace swift
{
	class AssetManager;
	class State
	{
		public:
			State(sf::RenderWindow& win, AssetManager& am);
			virtual ~State();
			
			enum Type
			{
				MainMenu = 0,
				SettingsMenu,
				Play,
				Exit
			};
			
			virtual void setup() = 0;
			virtual void handleEvent(sf::Event &event) = 0;
			virtual void update(sf::Time dt) = 0;
			virtual void draw(float e) = 0;
			virtual bool switchFrom() = 0;
			virtual Type finish() = 0;

		protected:
			/* Environment */
			sf::RenderWindow& window;
			AssetManager& assets;
			
			/* Input */
			KeyboardManager keyboard;
			MouseManager mouse;
			
			Type returnType;
	};
}

#endif // STATE_HPP
