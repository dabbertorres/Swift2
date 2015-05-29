#ifndef GAMEMENU_HPP
#define GAMEMENU_HPP

#include "GameState.hpp"

/* GUI headers */
#include "GUI/Window.hpp"

#include "KeyBindings/KeyboardManager.hpp"
#include "KeyBindings/MouseManager.hpp"

namespace tg
{
	class GameMenu : public GameState
	{
		public:
			GameMenu(sf::RenderWindow& win, GameAssets& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set, swift::Settings& dic, swift::StateMachine& sm);
			~GameMenu() = default;

			virtual void handleEvent(const sf::Event& event);
			virtual void update(const sf::Time& dt);
			virtual void draw();

		private:
			void setupGUI();
			cstr::Window gui;
			
			swift::KeyboardManager keyboard;
			swift::MouseManager mouse;
	};
}

#endif // GAMEMENU_HPP
