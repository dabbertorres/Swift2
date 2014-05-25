#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/* Input headers */
#include "../KeyBindings/KeyboardManager.hpp"
#include "../KeyBindings/MouseManager.hpp"

/* Resource headers */
#include "../ResourceManager/AssetManager.hpp"

/* Scripting headers */
#include "../Scripting/Script.hpp"

namespace swift
{	
	class State
	{
		public:
			State(sf::RenderWindow& win, AssetManager& am);
			virtual ~State();
			
			enum Type
			{
				MainMenu,
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
			void updateScripts();
			
			/* Environment */
			sf::RenderWindow& window;
			AssetManager& assets;
			
			/* Input */
			KeyboardManager keyboard;
			MouseManager mouse;
		
			/* Scripting */
			std::vector<Script*> activeScripts;
			
			Type returnType;
	};
}

#endif // STATE_HPP
