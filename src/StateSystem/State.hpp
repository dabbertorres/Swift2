#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "StateMachine.hpp"

/* Input headers */
#include "../KeyBindings/KeyboardManager.hpp"
#include "../KeyBindings/MouseManager.hpp"

namespace swift
{
	class AssetManager;
	class Settings;
	class SoundPlayer;
	class MusicPlayer;

	class State
	{
		public:
			State(sf::RenderWindow& win, AssetManager& am, SoundPlayer& sp, MusicPlayer& mp, Settings& set, Settings& dic, StateMachine& sm);
			virtual ~State();

			virtual void handleEvent(sf::Event& event) = 0;
			virtual void update(sf::Time dt) = 0;
			virtual void draw(float e) = 0;
			virtual bool switchFrom();

		protected:
			/* Environment */
			sf::RenderWindow& window;
			AssetManager& assets;
			SoundPlayer& soundPlayer;
			MusicPlayer& musicPlayer;
			Settings& settings;
			Settings& dictionary;
			StateMachine& states;

			/* Input */
			KeyboardManager keyboard;
			MouseManager mouse;

			bool shouldReturn;
	};
}

#endif // STATE_HPP
