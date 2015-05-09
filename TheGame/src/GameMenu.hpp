#ifndef GAMEMENU_HPP
#define GAMEMENU_HPP

#include "../src/StateSystem/State.hpp"

/* GUI headers */
#include "../src/GUI/Window.hpp"

namespace tg
{
	class GameMenu : public swift::State
	{
		public:
			GameMenu(sf::RenderWindow& win, swift::AssetManager& am, swift::SoundPlayer& sp, swift::MusicPlayer& mp, swift::Settings& set, swift::Settings& dic,
			         swift::StateMachine& sm);
			~GameMenu();

			virtual void handleEvent(sf::Event& event);
			virtual void update(sf::Time dt);
			virtual void draw(float e);

		private:
			void setupGUI();
			cstr::Window gui;
	};
}

#endif // GAMEMENU_HPP
